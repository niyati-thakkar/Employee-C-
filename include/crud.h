#ifndef _CRUD_H_
#define _CRUD_H_

#include "Employee.h"
#include <string>
#include<optional>
#include<map>
#include<vector>
#include "database.h"
#include "../sqlite/sqlite3.h"
#include<vector>

namespace QueryE {
	template<typename T1, typename T2>
	std::string viewQueryC(T2& e, std::vector<std::string> cols) {
		std::string fields = "";
		for (auto& col : cols) {
			fields += col + ", ";
		}
		auto t2 = T2::getTableName();
		auto t1 = T1::getTableName();
		std::string query = std::string{ "SELECT " } + fields.substr(0, fields.length() - 2) + std::string{ " from " } + t1 + " JOIN " + t2 + " ON " + t1 + "." + T2::getMap()[0].name + " = " + t2 + "." + T2::getMap()[0].name + ";";
		return query;
	}

	std::string removeQuery(std::string tablename) {
		return std::string{ "DELETE FROM " } + tablename;
	}

	template<typename T1, typename T2 = T1>
	std::string whereQuery(T1& e, getsetmap<T2> map) {
		std::string table = T2::getTableName();

		std::string query = std::string{ " WHERE " } + table + "." + map.name + " = '" + (e.*map.getter)() + "';";
		return query;
	}

	template<typename T1>
	std::string viewQuery(T1& e, std::vector<std::string> cols) {
		std::string fields = "";
		for (auto& col : cols) {
			fields += col + ", ";
		}

		auto table = T1::getTableName();
		std::string query = std::string{ "SELECT " } + fields.substr(0, fields.length() - 2) + std::string{ " from " } + table + ";";

		return query;
	}

	template<typename T1>
	std::string updateQuery(T1& e, std::vector<int> cols) {
		auto& map = T1::getMap();
		std::string query = "UPDATE " + T1::getTableName() + " SET ";
		for (auto& id : cols) {
			query = query + map[id].name + " = '" + (e.*map[id].getter)() + "', ";
		}
		query = query.substr(0, query.length() - 2);
		return query;
	}
	
	template<typename T1>
	std::string insertQuery(T1& e) {
		std::string fields = "";
		std::string input = "";
		auto& map = T1::getMap();
		if (map.find(0) != map.end()) {
			auto strct = map[0];
			if (auto h = (e.*strct.getter)(); h.length() > 0) {
				fields += strct.name + ", ";
				input += std::string{ "'" } + h + std::string{ "', " };
			}
		}
		for (int i = 2; i <= T1::getLastKey(); i++) {
			auto& strct = map[i];
			if (auto h = (e.*strct.getter)(); h.length() > 0) {
				fields += strct.name + ", ";
				input += std::string{ "'" } + h + std::string{ "', " };
			}
		}

		std::string query = "INSERT INTO " + T1::getTableName() + " (" + fields.substr(0, fields.length() - 2) + ") VALUES(" + input.substr(0, input.length() - 2) + "); ";
		std::cout << query << "\n";
		return query;
	}
}

namespace CRUD {
	

	/**********************************************************************************		miscelaneous	*************************************************************************************/ 
	std::string isOpt = " (Note - This field is optional. Enter '#' to keep it blank!)";
	template<typename T1>
	void clear(T1& e) {
		e = T1{};
	}
	bool isKeyPresent(std::string table, std::string col, std::string val) {
		Database db;
		return db.valueExistsInTable(table, col, val);

	}

	/**********************************************************************************		miscelaneous	*************************************************************************************/


	

	template<typename T1>
	std::string whereHelper(T1& e) {
		auto& map = T1::getMap();
		int i = 1;
		for (auto& [id, strct] : map) {
			std::cout << i++ << ". " << strct.name << "\n";
		}
		int selection;
		std::cin >> selection;
		if (selection <= 0 || selection > T1::getLastKey()) return "";
		do {
			if (Utility::getUserInput(e, map[selection])) break;
		} while (Utility::tryAgain());

		return QueryE::whereQuery(e, map[selection]);
	}
	template<typename T1, typename T2>
	std::pair<std::string, std::string> whereHelper(T1& e, std::map<int, getsetmap<T1>>& map1, std::map<int, getsetmap<T2>>& map2) {
		int i = 2;
		for (; i <= e.T2::getLastKey(); i++) {
			std::cout << i << ". " << map2[i].name << "\n";
		}
		i++;
		for (; i - e.T2::getLastKey() <= e.T1::getLastKey(); i++) {
			std::cout << i << ". " << map1[i - e.T2::getLastKey()].name << "\n";
		}
		int selection;
		std::cin >> selection;
		if (selection <= 0 || selection >= i) return std::make_pair("", "");
		if (selection <= e.T2::getLastKey()) {
			Utility::getUserInput(e, map1[selection]);
			return std::make_pair(e.T2::getTableName(), QueryE::whereQuery(e, map1[selection]));
		}
		else {
			selection -= e.T2::getLastKey();
			Utility::getUserInput(e, map2[selection]);
			return std::make_pair(T2::getTableName(), QueryE::whereQuery(e, map2[selection]));
		}

	}
	
	/**********************************************************************************		insert	*************************************************************************************/

	template<typename T1, typename T2 = T1>
	bool insertHelper(T1& e, std::map<int, getsetmap<T2>>& map) {

		for (auto i = 2; i <= T2::getLastKey(); i++) {
			if (!map[i].isOptional) {
				if (!Utility::getUserInput(e, map[i])) {
					std::cout << "Entered invalid value, Sorry can't insert into Database!" << "\n";
					clear(e);
					return false;
				}
			}
			else {
				std::cout << "Enter " << map[i].name << isOpt << "\n";
				std::string temp;
				Utility::setInput(temp);
				if (temp[0] == '#' || !(e.*map[i].setter)(temp)) {
					std::cout << "Optional Field is left blank!" << "\n";
				}
			}
		}

		return true;

	}

	template<typename T1, typename T2>
	bool insertC(T2& e) {
		auto& empmap = T1::getMap();
		Database db;
		if (insertHelper(e, empmap)) {
			db.executeQueryD(QueryE::insertQuery<T1>(e));
			(e.*T2::getMap()[0].setter)(std::to_string(db.lastInsertedValue()));
			auto& map = T2::getMap();
			if (insertHelper(e, map)) {
				db.executeQueryD(QueryE::insertQuery(e));
				e.getAddress().setEmpId(e.getEmpId());
				if (!insertHelper(e.getAddress(), e.getAddress().getMap())) {
					std::cout << "Address field is left optional!" << "\n";
				}
				db.executeQueryD(QueryE::insertQuery(e.getAddress()));
			}
			else {
				std::string query = QueryE::removeQuery(T1::getTableName()) + QueryE::whereQuery(e, T2::getMap()[0]);
				if (db.executeQueryD(query));
				clear(e);
				return false;
			}
		}
		return true;
	}

	template<typename T1>
	bool insert(T1& e) {
		Database db;
		auto& empmap = T1::getMap();
		if (insertHelper(e, empmap)) {
			if(db.executeQueryD(QueryE::insertQuery(e)))
				return true;
		}
		return false;
	}




	/**********************************************************************************		view	*************************************************************************************/


	template<typename T1>
	void viewHelper(bool takeAll, std::string table, std::map<int, getsetmap<T1>>& map, size_t lastkey, std::vector<std::string>& cols) {
		if (takeAll) {
			for (auto i = 1; i <= lastkey; i++) {
				cols.push_back(table + "." + map[i].name);
			}
		}
		else {
			for (int i = 1; i <= lastkey; i++) {
				std::cout << "1. Select " << map[i].name << "\n";
				std::cout << "2. Discard " << map[i].name << "\n";
				char temp;
				std::cin >> temp;
				if (temp == '1') {
					cols.push_back(table + "." + map[i].name);
				}

			}
		}
	}

	template<typename T1, typename T2 = T1>
	bool viewC(T2& e) {
		std::string tableID{ "View by " };
		tableID += T2::getTableName() + " ID";
		int option = Utility::takeOption("View Entire Table", "View by EmpID", tableID, "View by Column Value");
		int takeAll;
		std::cout << "1. View Selected Columns" << "\n";
		std::cout << "2. View All Columns" << "\n";
		std::cin >> takeAll;
		std::vector<std::string> cols;
		std::string query;
		auto table1 = T1::getTableName();
		auto table2 = T2::getTableName();
		auto& empmap = T1::getMap();
		auto& map = T2::getMap();
		viewHelper(takeAll - 1, table1, empmap, T1::getLastKey(), cols);
		viewHelper(takeAll - 1, table2, map, T2::getLastKey(), cols);
		query = QueryE::viewQueryC<T1, T2>(e, cols);
		switch (option) {
		case 0:
			return true;
		case 2:
		{
			do {
				if (Utility::getUserInput(e, T2::getMap()[0])) break;
				if (!Utility::tryAgain()) return true;
			} while (true);
			query = query.substr(0, query.length() - 1) + QueryE::whereQuery(e, T2::getMap()[0]);
			break;
		}
		case 3: {
			do {
				if (Utility::getUserInput(e, T2::getMap()[1])) break;
				if (Utility::tryAgain()) return true;
			} while (true);
			query = query.substr(0, query.length() - 1) + QueryE::whereQuery(e, T2::getMap()[1]);
			break;
		}
		case 4: {
			query = query.substr(0, query.length() - 1) + whereHelper(e, map, empmap).second;
			break;
		}
		}
		Database db;
		std::cout << query << "\n";
		std::cout << db.selectQueryD(query) << "\n";
		return true;
	}


	template<typename T1>
	bool view(T1& e) {
		std::string tableID{ "View by " };
		tableID += T1::getTableName() + " ID";
		int option = Utility::takeOption("View Entire Table", tableID, "View by Column value");
		if (option == 0) return false;
		int takeAll = Utility::takeOption("View Selected Columns", "View All Columns");
		if (takeAll == 0) return false;
		std::vector<std::string> cols;
		std::string query;
		auto table1 = T1::getTableName();
		auto& map = T1::getMap();
		viewHelper(takeAll - 1, table1, map, T1::getLastKey(), cols);
		query = QueryE::viewQuery(e, cols);
		switch (option) {
		case 2:
		{
			do {
				if (Utility::getUserInput(e, T1::getMap()[1])) break;
			} while (Utility::tryAgain());
			query = query.substr(0, query.length() - 1) + QueryE::whereQuery(e, T1::getMap()[1]);
			break;
		}
		case 3: {
			query = query.substr(0, query.length() - 1) + whereHelper(e);
			break;
		}
		}
		Database db;
		std::cout << query << "\n";
		std::cout << db.selectQueryD(query) << "\n";
		return true;
	}


	/**********************************************************************************		update		*************************************************************************************/

	template<typename T1, typename T2>
	bool updateHelper(T1& e, std::map<int, getsetmap<T2>> map, std::vector<int>& indices) {
		for (auto i = 2; i <= T2::getLastKey(); i++) {
			int input = Utility::takeOption(("Update " + map[i].name), ("Discard " + map[i].name));
			if (input == 0) {
				clear(e);
				return false;
			}
			if (input == 1) {
				do {
					if (Utility::getUserInput(e, map[i])) {
						indices.push_back(i);
					}
				} while (Utility::tryAgain());
			}
		}
		return true;
	}

	template<typename T1, typename T2>
	bool updateC(T2& e) {
		int option = Utility::takeOption("Update by EmpID", (std::string{ "Update by " } + e.getTableName() + " ID"));
		std::string wherequery1, wherequery2;
		if (option == 0) return true;
		if (option == 1) {
			do {
				if (Utility::getUserInput(e, T2::getMap()[0])) {
					if (Database db; db.valueExistsInTable(T2::getTableName(), T2::getMap()[0].name, (e.*T2::getMap()[0].getter)())) {
						wherequery1 = QueryE::whereQuery(e, T2::getMap()[0]);
						(e.*T1::getMap()[1].setter)((e.*T2::getMap()[0].getter)());
						wherequery2 = QueryE::whereQuery(e, T1::getMap()[1]);
						break;
					}
				}
			} while (Utility::tryAgain());
		}
		else {
			do {
				if (Utility::getUserInput(e, T2::getMap()[1])) {
					if (Database db; db.valueExistsInTable(T2::getTableName(), T2::getMap()[1].name, (e.*T2::getMap()[1].getter)())) {
						wherequery1 = QueryE::whereQuery(e, T2::getMap()[1]);
						(e.*T1::getMap()[1].setter)(db.getColValue(T2::getTableName(), T2::getMap()[1].name, (e.*T2::getMap()[1].getter)(), T2::getMap()[0].name));
						wherequery2 = QueryE::whereQuery(e, T1::getMap()[1]);
						break;
					}
				}
			} while (Utility::tryAgain());
		}
		std::vector<int> indices1;
		updateHelper(e, T1::getMap(), indices1);
		std::string query1 = QueryE::updateQuery(e, indices1) + wherequery1;

		Database db;
		if (!db.executeQueryD((query1))) return false;


		std::vector<int> indices2;
		updateHelper(e, T2::getMap(), indices2);
		std::string query2 = QueryE::updateQuery(e, indices2) + wherequery2;

		db.executeQueryD((query2));
		return true;
	}

	template<typename T1>
	bool update(T1& e) {
		int option = Utility::takeOption("Update by ID");
		if (option == 0) return true;
		std::string query;
		do {
			if (Utility::getUserInput(e, e.getMap()[1])) {
				if (Database db; db.valueExistsInTable(e.getTableName(), e.getMap()[1].name, (e.*e.getMap()[1].getter)())) {
					query = QueryE::whereQuery(e, e.getMap()[1]);
					break;
				}
			}
		} while (Utility::tryAgain());

		std::vector<int> indices;
		updateHelper(e, T1::getMap(), indices);
		query = QueryE::updateQuery(e, indices) + query;

		Database db;
		db.executeQueryD(query);
		return true;
	}


	/**********************************************************************************		remove	*************************************************************************************/

	template<typename T1>
	bool remove(T1& e) {
		int option = Utility::takeOption("Delete by ID", "Delete by column value");
		if (option == 0) return true;
		std::string query{ QueryE::removeQuery(T1::getTableName()) };
		if (option == 1) {
			do {
				if (Utility::getUserInput(e, T1::getMap()[1])) {
					if (Database db; db.valueExistsInTable(T1::getTableName(), T1::getMap()[1].name, (e.*T1::getMap()[1].getter)())) {
						query += QueryE::whereQuery(e, T1::getMap()[0]);
						break;
					}
				}
			} while (Utility::tryAgain());
		}
		else {
			query += whereHelper(e);
		}
		Database db;
		db.executeQueryD((query));
		return true;
	}
	template<typename T1, typename T2>
	bool removeC(T2& e) {
		int option = Utility::takeOption("Delete by EmpID", (std::string{ "Delete by " } + T2::getTableName() + " ID"), "Delete by column value");
		if (option == 0) return true;
		std::string query;
		std::string tablename;
		switch (option) {
		case 1: {
			do {
				if (Utility::getUserInput(e, T2::getMap()[0])) {
					if (Database db; db.valueExistsInTable(T2::getTableName(), T2::getMap()[0].name, (e.*T2::getMap()[0].getter)())) {
						query += QueryE::whereQuery(e, T2::getMap()[0]);
						break;
					}
				}
			} while (Utility::tryAgain());
		}
		case 2: {
			do {
				if (Utility::getUserInput(e, T2::getMap()[1])) {
					if (Database db; db.valueExistsInTable(T2::getTableName(), T2::getMap()[1].name, (e.*T2::getMap()[1].getter)())) {
						query += QueryE::whereQuery(e, T2::getMap()[1]);
						break;
					}
				}
			} while (Utility::tryAgain());
		}
		case 3: {
			auto temp = whereHelper(e, T2::getMap(), T1::getMap());
			tablename = temp.first;
			query = temp.second;

		}
		}
		Database db;
		db.executeQueryD(std::string{ QueryE::removeQuery(tablename) + query });
		return true;
	}

}

#endif