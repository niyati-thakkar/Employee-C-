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
template<typename T>
class Query {
public:
	static std::string insertQuery(T e) {

		std::string fields = "";
		std::string input = "";
		auto& map = e.getMap();
		for (int i = 2;i < map.size() + 1; i++) {
			auto& strct = map[i];
			if (auto h = (e.*strct.getter)(); h.length() > 0 ) {
				fields += strct.name + ", ";
				input += std::string{ "'" } + h + std::string{ "', " };
			}
		}

		std::string query = "INSERT INTO " + e.getTableName() + " (" + fields.substr(0, fields.length() - 2) + ") VALUES(" + input.substr(0, input.length() - 2) + "); ";
		std::cout << query << "\n";
		return query;
	}
	

	static std::string deleteQuery(T& e, int selection) {
		auto& strct = e.getMap()[selection];
		std::string query = std::string{ "DELETE FROM " } + e.getTableName() + " WHERE " + strct.name + " = '" + (e.*strct.getter)() + "'; ";
		std::cout << query << "\n";
		return query;
	}

	static std::string selectQuery(T& e, int selection) {
		auto& strct = e.getMap()[selection];
		std::string query = std::string{ "SELECT * FROM " } + e.getTableName() + " WHERE " + strct.name + " = '" + (e.*strct.getter)() + "'; ";
		std::cout << query << "\n";
		return query;
	}

	static std::string selectQuery(T& e, std::vector<std::string> cols) {

		std::string fields = "";
		for (auto& col : cols) {
			fields += col + ", ";
		}

		std::string query = "SELECT " + fields.substr(0, fields.length() - 2) + " from " + e.getTableName() + ";";

		return query;
	}

	static std::string selectQuery(T& e) {
		std::string query = "SELECT * FROM " + e.getTableName() + ";";
		return query;
	}

	static std::string updateQuery(T& e, int where, std::vector<int>& what) {
		auto& map = e.getMap();
		std::string query = "UPDATE " + e.getTableName() + " SET ";
		for (auto& id : what) {
			query = query + map[id].name + " = '" + (e.*map[id].getter)() + "', ";
		}
		query = query.substr(0, query.length() - 2) + " WHERE " + map[where].name + " = '" + (e.*map[where].getter)() + "';";
		return query;
	}

};



template<typename T>
class CRUD {
private:
	inline static std::map<int, std::pair<std::string, std::string>> operations = {
		{1, {std::string{"="}, std::string{"equal to"}}},
		{2, {std::string{"<"},std::string{"less than"}}},
		{3, {std::string{">"}, std::string{"greater than"}}},
		{4, {std::string{"<="}, std::string{"less than or equal to"}}},
		{5, {std::string{">="}, std::string{"greater than or equal to"}}},
		{6, {std::string{"!="}, std::string{"not equal to"}}}

	};
	inline static std::string isOpt = " (Note - This field is optional. Enter '#' to keep it blank!)";
public:
	static void clear(T& e) {
		e = T{};
	}
	
	static bool insertC(T& e, int start) {
		auto& map = e.getMap();
		for (int i = start;i < map.size() + 1; i++) {
			if (!map[i].isOptional){
				if (!Utility::getUserInput(e, i)) {
					std::cout << "Entered invalid value, Sorry can't insert into Database!"<< "\n";
					clear(e);
					return false;
				}
			}
			else {
				std::cout << "Enter " << map[i].name << isOpt <<"\n";
				std::string temp;
				std::cin >> temp;
				if (temp[0] == '#' || !(e.*map[i].setter)(temp)) {
					std::cout << "Optional Field is left blank!"<<"\n";
				}
			}
		}
		
		Database db;
		std::cout << db.executeQueryD(Query<T>::insertQuery(e)) << "\n";
		(e.*map[1].setter)(std::to_string(db.lastInsertedValue()));
		return true;
	}
	static bool deleteC(T& e) {

		std::cout << "Delete on the basis of:" << "\n";
		std::cout << Utility::backMessage << "\n";
		int i = 1;
		auto& map = e.getMap();
		for (auto& [id, strct] : map) {
			std::cout << i++ << ". " << strct.name << "\n";
		}
		int selection;
		std::cin >> selection;
		if (selection == 0) return true;
		if (selection < 0 || selection > map.size()) {
			if (Utility::tryAgain()) {
				deleteC(e);
			}
			else {
				return false;
			}
		}

		if(!Utility::getUserInput(e, selection)){
			std::cout << "Entered invalid value, Sorry can't delete from Database!" << "\n";
			return false;
		}


		Database db;
		std::cout << db.executeQueryD(Query<T>::deleteQuery(e, selection)) << "\n";
		return true;
	}

	
	static bool viewC(T& e) {
		int opt = Utility::takeOption("View Entire Table", "View by Columns", "View by Rows");
		if (opt == 0) return true;
		std::string query;
		if (opt == 1) {
			query = Query<T>::selectQuery(e);
		}
		if (opt == 2) {
			std::vector<std::string> cols;
			for (auto& [id, strct] : e.getMap()) {
				std::cout << "1. Select" << strct.name << "\n";
				std::cout << "2. Discard" << strct.name << "\n";
				std::string temp;
				std::cin >> temp;
				if (temp == "1") {
					cols.push_back(strct.name);
				}
			}
			if (cols.size() == 0) {
				std::cout << "No Columns Selected!";
				return true;
			}
			query = Query<T>::selectQuery(e, cols);
		}
		if (opt == 3) {
			std::cout << "Select on the basis of:" << "\n";
			int i = 1;
			auto& map = e.getMap();
			for (auto& [id, strct] : map) {
				std::cout << i++ << ". " << strct.name << "\n";
			}
			int selection;
			std::cin >> selection;
			if (selection == 0) return true;
			if (selection < 0 || selection > map.size()) {
				if (Utility::tryAgain()) {
					viewC(e);
				}
				else {
					return false;
				}
			}

			if(!Utility::getUserInput(e, selection)){
				std::cout << "Entered invalid value, Sorry can't view from Database!" << "\n";
				return false;
			}
			query = Query<T>::selectQuery(e, selection);
		}
		Database db;
		std::cout << db.selectQueryD(query) << "\n";
	}
	static bool updateC(T& e) {
		int opt1 = Utility::takeOption("Update by ID", "Update by Column value");
		if (opt1 == 0) return true;
		auto& map = e.getMap();
		std::string query;
		int where = 0;
		if (opt1 == 1) {
			where = 1;
		}
		if (opt1 == 2) {
			std::cout << "Update on the basis of:" << "\n";
			int i = 1;
			for (auto& [id, strct] : map) {
				std::cout << i++ << ". " << strct.name << "\n";
			}
			std::cin >> where;
			if (where == 0) return true;
			if (where < 0 || where > map.size()) {
				if (Utility::tryAgain()) {
					updateC(e);
				}
				else {
					return false;
				}
			}
		}
		if (!Utility::getUserInput(e, where)) {
			std::cout << "Entered invalid value, Sorry can't update from Database!" << "\n";
			return false;
		}

		int opt2 = Utility::takeOption("Update Single Value", "Update multiple Values");
		std::vector<int> updated;

		if (opt2 == 0) return updateC(e);
		if (opt2 == 1) {
			std::cout << "Select the value to be updated:" << "\n";
			int i = 1;
			for (int i = 2;i < map.size() + 1; i++) {
				auto& strct = map[i];
				std::cout << i-1 << ". " << strct.name << "\n";
			}
			int what;
			std::cin >> what;
			if (what <= 0 || what > map.size()-1) {
				if (Utility::tryAgain()) {
					updateC(e);
				}
				else {
					return false;
				}
			}
			if (!Utility::getUserInput(e, what+1)) {
				std::cout << "Entered invalid value, Sorry can't update from Database!";
					return false;
			}
			else {
				updated.push_back(what+1);
			}
		}
		if (opt2 == 2) {
			for (int i = 2;i < map.size() + 1; i++) {
				std::cout << "1. Update" << map[i].name << "\n";
				std::cout << "2. Discard" << map[i].name << "\n";
				std::string temp;
				std::cin >> temp;
				if (temp == "1") {
					if (!Utility::getUserInput(e, i)) {
						std::cout << "Entered invalid value, Sorry can't update from Database!";
							return false;
					}
					updated.push_back(i);
				}
				
			}
		}
		
		Database db;
		std::cout << db.executeQueryD(Query<T>::updateQuery(e, where, updated)) << "\n";
		return 0;
	}
	static bool isKeyPresent(std::string table, std::string val) {
		Database db;
		return db.valueExistsInTable(table, val);
	}
	static bool deleteEmp(std::string id) {
		Database db;
		std::cout << db.executeQueryD(std::string{ "DELETE FROM EMPLOYEE WHERE ID = '" } + id + "';") << "\n";
		return true;
	}
	
};
#endif