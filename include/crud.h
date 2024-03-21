#ifndef _CRUD_H_
#define _CRUD_H_

#include "Employee.h"
#include <string>
#include<optional>
#include<map>
#include<vector>
#include "database.h"
#include "../sqlite/sqlite3.h"
#include <type_traits>
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
	std::string whereQuery(T2& e, getsetmap<T1> map) {
		std::string table = T1::getTableName();

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

	template<typename T1, typename T2>
	std::string updateQuery(T2& e, std::vector<int> cols) {
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
		return query;
	}
}

namespace CRUD {
	
	
	/**********************************************************************************		miscelaneous	*************************************************************************************/ 
	std::string isOpt = " (Note - This field is optional. Enter '#' to keep it blank!)";
	std::string invalid = "Invalid Input!";
	std::string valuenotexits = "Value doesn't exists!";
	template<typename T1>
	void clear(T1& e) {
		e = T1{};
	}
	bool isKeyPresent(std::string table, std::string col, std::string val) {
		Database db;
		return db.valueExistsInTable(table, col, val);

	}

	/*********************************************************************		where	*************************************************************************************/


	

	template<typename T1>
	std::string whereHelper(T1& e) {
		auto& map = T1::getMap();
		int i = 1;
		for (; i + 1 <= T1::getLastKey(); i++) {
			std::cout << i << ". " << map[i + 1].name << "\n";
		}
		int selection;
		if (Utility::setInput(selection)) {
			if (selection > 0 && selection < T1::getLastKey())
				if (Utility::getUserInput(e, map[selection+1]))
					return QueryE::whereQuery(e, map[selection+1]);
		}
		return "";
	}
	template<typename T1, typename T2>
	std::pair<std::string, std::string> whereHelper(T2& e, std::map<int, getsetmap<T1>>& map1, std::map<int, getsetmap<T2>>& map2) {
		int i = 1;
		for (; i+1 <= T1::getLastKey(); i++) {
			std::cout << i << ". " << map1[i+1].name << "\n";
		}
		for (; i - T1::getLastKey() + 1 <= T2::getLastKey(); i++) {
			std::cout << i << ". " << map2[i - T1::getLastKey() + 1].name << "\n";
		}
		int selection;
		if (Utility::setInput(selection)) {
			if (selection > 0 && selection < i) {
				if (selection < T1::getLastKey()) {
					if(Utility::getUserInput(e, map1[selection+1]))
						return std::make_pair(T1::getTableName(), QueryE::whereQuery(e, map1[selection+1]));
				}
				else {
					selection -= T1::getLastKey();
					if(Utility::getUserInput(e, map2[selection+1]))
						return std::make_pair(T2::getTableName(), QueryE::whereQuery(e, map2[selection+1]));
				}
			}
		}
		return std::make_pair("", "");
	}
	
	/*************************************************		insert		*************************************************************************************/

	template<typename T1, typename T2 = T1>
	bool insertHelper(T1& e, std::map<int, getsetmap<T2>>& map) {

		for (auto i = 2; i <= T2::getLastKey(); i++) {
			if (!map[i].isOptional) {
				if (!Utility::getUserInput(e, map[i])) {
					clear(e);
					return false;
				}
			}
			else {
				std::cout << "Enter " << map[i].name << isOpt << "\n";
				std::string temp;
				
				if (Utility::setInput(temp)) {
					if (temp[0] == '#' || !(e.*map[i].setter)(temp)) {
						std::cout << "Optional Field is left blank!" << "\n";
					}
				}
				else {
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
		std::string table1 = T2::getTableName();
		if (insertHelper(e, empmap)) {
			if (db.executeQueryD(QueryE::insertQuery<T1>(e))) {
				(e.*T2::getMap()[0].setter)(std::to_string(db.lastInsertedValue()));
				auto& map = T2::getMap();
				if (insertHelper(e, map)) {
					if (db.executeQueryD(QueryE::insertQuery(e))) {
						e.getAddress().setEmpId(e.getEmpId());
						std::string table2 = e.getAddress().getTableName();
						if (!insertHelper(e.getAddress(), e.getAddress().getMap()) || !db.executeQueryD(QueryE::insertQuery(e.getAddress()))) {
							Database::logger.Warn(table2 + " Insertion Failed!");
						}
						else {
							Database::logger.Info(table2 + " inserted successfully!");
						}
						
						Database::logger.Info(table1 + " inserted successfully!");
						return true;
					}
				}
				else {
					std::string query = QueryE::removeQuery(T1::getTableName()) + QueryE::whereQuery(e, T2::getMap()[0]);
					if (db.executeQueryD(query)) {
						clear(e);
					}
					else {
						exit(0);
					}
					
				}
			}
			Database::logger.Error(table1 + " Insertion Failed!");
			
		}
		
	}

	template<typename T1>
	bool insert(T1& e) {
		Database db;
		auto& empmap = T1::getMap();
		std::string table1 = T1::getTableName();
		if (insertHelper(e, empmap)) {
			if (db.executeQueryD(QueryE::insertQuery(e))) {
				Database::logger.Info(table1 + " inserted successfully!");
				return true;
			}
				
		}
		Database::logger.Error(table1 + " Insertion Failed!");
		return false;
	}

	/********************************************************		view	*************************************************************************************/

	template<typename T1>
	void viewHelper(bool takeAll, std::string table, std::map<int, getsetmap<T1>>& map, size_t lastkey, std::vector<std::string>& cols) {
		if (takeAll) {
			for (auto i = 1; i <= lastkey; i++) {
				cols.push_back(table + "." + map[i].name);
			}
		}
		else {
			for (int i = 1; i <= lastkey; i++) {
				int opt = Utility::takeOption(false, "Select" + map[i].name, "Discard" + map[i].name);
				if (opt == 0) return;
				if (opt == 1) {
					cols.push_back(table + "." + map[i].name);
				}

			}
		}
	}

	template<typename T1, typename T2>
	bool viewC(T2& e) {
		int option = Utility::takeOption(true, "View Entire Table", "View by EmpID", std::string{ "View by " } + T2::getTableName() + " ID", "View by Column Value");
		if (option == 0) return false;
		std::string wquery;
		std::vector<std::string> cols;
		auto table1 = T1::getTableName();
		auto table2 = T2::getTableName();
		auto& empmap = T1::getMap();
		auto& map = T2::getMap();
		switch (option) {
		case 2:
		{
				if (Utility::getUserInput(e, T2::getMap()[0])) {
					wquery = QueryE::whereQuery(e, T2::getMap()[0]);
					break;
				} 
				Database::logger.Error("Invalid Input");
				return false;
		}
		case 3: {
				if (Utility::getUserInput(e, T2::getMap()[1])) {
					wquery = QueryE::whereQuery(e, T2::getMap()[1]);
					break;
				} 
				Database::logger.Error("Invalid Input");
				return false;
			
		}
		case 4: {
			wquery = whereHelper<T1, T2>(e, empmap, map).second;
			if (wquery.length() == 0) {
				Database::logger.Error("Invalid Input");
				return false;
			}
			break;
		}
		}
		int takeAll = Utility::takeOption(true, "View Selected Columns", "View All Columns");
		if (takeAll == 0) return false;
		viewHelper(takeAll - 1, table1, empmap, T1::getLastKey(), cols);
		viewHelper(takeAll - 1, table2, map, T2::getLastKey(), cols);
		if (cols.size() == 0) {
			Database::logger.Warn("No Columns Selected");
			return false;
		}
		std::string query = QueryE::viewQueryC<T1, T2>(e, cols);
		if (option != 1) query = query.substr(0, query.length() - 1) + wquery;
		Database db;
		if (db.selectQueryD(query)) {
			Database::logger.Info("Successfully Fetched");
			return true;
		}
			
		return false;
	}


	template<typename T1>
	bool view(T1& e) {
		std::string tableID{ "View by " };
		tableID += T1::getTableName() + " ID";
		int option = Utility::takeOption(true, "View Entire Table", tableID, "View by Column value");
		if (option == 0) return false;
		std::vector<std::string> cols;
		std::string wquery;
		auto table1 = T1::getTableName();
		auto& map = T1::getMap();
		
		switch (option) {
		case 2:
		{
			if (Utility::getUserInput(e, T1::getMap()[1])) {
				wquery = QueryE::whereQuery(e, T1::getMap()[1]);
				break;
			}
			Database::logger.Error("Invalid Input");
			return false;
			
		}
		case 3: {
			wquery = whereHelper(e);
			if (wquery.length())
				break;
			Database::logger.Error("Invalid Input");
			return false;
		}
		}

		int takeAll = Utility::takeOption(false, "View Selected Columns", "View All Columns");
		if (takeAll == 0) return false;
		viewHelper(takeAll - 1, table1, map, T1::getLastKey(), cols);
		if (cols.size() == 0) {
			Database::logger.Warn("No Columns Selected");
			return false;
		}
		std::string query = QueryE::viewQuery(e, cols);
		if (wquery.length() > 0) query = query.substr(0, query.length() - 1) + wquery;

		Database db;
		if (db.selectQueryD(query))
			Database::logger.Info("Successfully Fetched");
			return true;
		return false;
	}


	/***********************************************		update		*************************************************************************************/

	template<typename T1, typename T2=T1>
	bool updateHelper(T2& e, std::map<int, getsetmap<T1>> map, std::vector<int>& indices) {
		for (auto i = 2; i <= T1::getLastKey(); i++) {
			int input = Utility::takeOption(false, ("Update " + map[i].name), ("Discard " + map[i].name));
			if (input == 0) {
				clear(e);
				return false;
			}
			if (input == 1) {
				if (Utility::getUserInput(e, map[i])) {
					indices.push_back(i);
				}
			}
		}
		return true;
	}

	template<typename T1, typename T2>
	bool updateC(T2& e) {
		int option = Utility::takeOption(true, "Update by EmpID", (std::string{ "Update by " } + T2::getTableName() + " ID"));
		std::string wherequery1, wherequery2;
		if (option == 0) return true;
		if (option == 1) {
			if (Utility::getUserInput(e, T2::getMap()[0])) {
				if (Database db; db.valueExistsInTable(T2::getTableName(), T2::getMap()[0].name, (e.*T2::getMap()[0].getter)())) {
					wherequery2 = QueryE::whereQuery(e, T2::getMap()[0]);
					(e.*T1::getMap()[1].setter)((e.*T2::getMap()[0].getter)());
					wherequery1 = QueryE::whereQuery(e, T1::getMap()[1]);
				}

				else {
					Database::logger.Error(valuenotexits);
					return false;
				}
			}
			else {
				Database::logger.Error(invalid);
				return false;
			}
				
		}
		else {
			if (Utility::getUserInput(e, T2::getMap()[1])) {
				if (Database db; db.valueExistsInTable(T2::getTableName(), T2::getMap()[1].name, (e.*T2::getMap()[1].getter)())) {
					wherequery2 = QueryE::whereQuery(e, T2::getMap()[1]);
					if (auto temp = db.getColValue(T2::getTableName(), T2::getMap()[1].name, (e.*T2::getMap()[1].getter)(), T2::getMap()[0].name); (e.*T1::getMap()[1].setter)(temp)) {
						wherequery1 = QueryE::whereQuery(e, T1::getMap()[1]);
					}
					else {
						Database::logger.Error("Some Error occured!");
						return false;
					}
				}
				else {
					Database::logger.Error(valuenotexits);
					return false;
				}
			}
			else{
				Database::logger.Error(invalid);
				return false;
			}
		}
		std::vector<int> indices1;
		updateHelper(e, T1::getMap(), indices1);
		Database db;
		bool done = false;
		if (indices1.size() != 0) {
			std::string query1 = QueryE::updateQuery<T1, T2>(e, indices1) + wherequery1;
			if (db.executeQueryD((query1))) {
				done = true;
			}
		}
	
		std::vector<int> indices2;
		updateHelper(e, T2::getMap(), indices2);
		if (indices2.size() != 0) {
			std::string query2 = QueryE::updateQuery<T2, T2>(e, indices2) + wherequery2;
			if (db.executeQueryD((query2))) {
				done = true;
			}
				
		}
		if (done) {
			Database::logger.Info("Successfully Executed Update!");
			return true;
		}
		return false;
		
	}

	template<typename T1>
	bool update(T1& e) {
		int option = Utility::takeOption(true, "Update by ID");
		if (option == 0) return true;
		std::string query;
		if (Utility::getUserInput(e, e.getMap()[1])) {
			if (Database db; db.valueExistsInTable(e.getTableName(), e.getMap()[1].name, (e.*e.getMap()[1].getter)())) {
				query = QueryE::whereQuery(e, e.getMap()[1]);
			}
			else {
				Database::logger.Error(valuenotexits);
				return false;
			}
				
		}
		else {
			Database::logger.Error(invalid);
			return false;
		}

		std::vector<int> indices;
		updateHelper(e, T1::getMap(), indices);
		query = QueryE::updateQuery<T1, T1>(e, indices) + query;
		Database db;
		if (db.executeQueryD(query)) {
			Database::logger.Info("Successfully Executed Update!");
			return true;
		}
		return true;
	}


	/**********************************************************************************		 remove		*************************************************************************************/

	template<typename T1>
	bool removeHelper(T1& e) {

	}
	
	template<typename T1>
	bool remove(T1& e) {
		int option = Utility::takeOption(true, "Delete by ID", "Delete by column value");
		if (option == 0) return true;
		std::string query{ QueryE::removeQuery(T1::getTableName()) };
		std::string wquery{};
		if (option == 1) {
			if (Utility::getUserInput(e, T1::getMap()[1])) {
				if (Database db; db.valueExistsInTable(T1::getTableName(), T1::getMap()[1].name, (e.*T1::getMap()[1].getter)())) {
					wquery = QueryE::whereQuery<T1, T1>(e, T1::getMap()[1]);
				}
				else {
					Database::logger.Error(valuenotexits);
					return false;
				}
			}
			else {
				Database::logger.Error(invalid);
				return false;
			}
		}
		else {
			wquery = whereHelper(e);
		}
		Database db;
		bool done = false;
		if (T1::getTableName() == "DEPARTMENT") {
			Database::logger.Warn("Note that Employees, Engineers, HR, and Managers, belonging to this deparment will also be deleted!");
			int todlt = Utility::takeOption(false, "Yes, Proceed!", "No, Go back to Previous Menu!");
			if (todlt == 2) {
				clear(e);
				return false;
			}
			else {
				if (db.turnCascadeOn() && db.executeQueryD((query + wquery))) {
					db.turnCascadeOff();
					return true;
				}
			}
		}
		else {
			std::string selectquery = QueryE::viewQuery(e, std::vector{ std::string{T1::getMap()[1].name} });
			selectquery = selectquery.substr(0, selectquery.length(0 - 1) + wquery;
			std::vector<std::string> empids;
			db.getPrimaryKeys(, empids);
			for (auto& t : empids)
			{

			}
		}
		
		if (done) {
			Database::logger.Info("Successfully Executed Delete");
			return true;
		}
	}
	template<typename T1, typename T2>
	bool removeC(T2& e) {
		//if constexpr ( std::is_same<T2, Manager>::value ||  std::is_same<T2, Engineer>::value ||  std::is_same<T2, HR>::value) {
		//	/*logger.Warn("On deleting " + T2::getTableName() + " will also cause deletion of Employees, ")*/
		//}
		int option = Utility::takeOption(true, "Delete by EmpID", (std::string{ "Delete by " } + T2::getTableName() + " ID"), "Delete by column value");
		if (option == 0) return true;
		std::string query;
		std::string tablename = T2::getTableName();
		switch (option) {
		case 1: {
			if (Utility::getUserInput(e, T2::getMap()[0])) {
				if (Database db; db.valueExistsInTable(T2::getTableName(), T2::getMap()[0].name, (e.*T2::getMap()[0].getter)())) {
					query = QueryE::whereQuery<T2, T2>(e, T2::getMap()[0]);
				}
				else {
					Database::logger.Error(valuenotexits);
					return false;
				}
			}
			else {
				Database::logger.Error(invalid);
				return false;
			}
			break;

		}
		case 2: {
			if (Utility::getUserInput(e, T2::getMap()[1])) {
				if (Database db; db.valueExistsInTable(T2::getTableName(), T2::getMap()[1].name, (e.*T2::getMap()[1].getter)())) {
					query = QueryE::whereQuery(e, T2::getMap()[1]);
					break;
				}
			}
			break;

		}
		case 3: {
			auto temp = whereHelper(e, T1::getMap(), T2::getMap());
			tablename = temp.first;
			query = temp.second;
			if (temp.first.size() == 0 || temp.second.size() == 0) {
				Database::logger.Error(invalid);
				return false;
			}

		}
		}
		Database db;
		if (db.executeQueryD(std::string{ QueryE::removeQuery(tablename) + query })) {
			Database::logger.Info("Successfully Executed Delete");
			return true;
		}
	}

}

#endif