#ifndef _CRUD_H_
#define _CRUD_H_
#include "Employee.h"
#include <string>
#include<optional>
#include<map>
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
	

	static std::string deleteQuery(T& e, getsetmap<T> strct) {
		std::string query = std::string{ "DELETE FROM " } + e.getTableName() + " WHERE " + strct.name + " = '" + (e.*strct.getter)() + "'; ";
		std::cout << query << "\n";
		return query;
	}

	static std::string selectQuery(T& e, getsetmap<T> strct) {
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
		std::cout << ("hii") << "\n";
	}
	
	static bool insertC(T& e) {
		auto& map = e.getMap();
		for (int i = 2;i < map.size() + 1; i++) {
			auto& strct = map[i];
			std::cout << "Enter " << strct.name << (strct.isOptional ? isOpt : "") << "\n";
			std::string temp;
			std::cin >> temp;
			if (!(e.*strct.setter)(temp)){
				std::cout << "Invalid " << strct.name << " (Try Again)" << "\n";
				std::cin >> temp;
				if (!(e.*strct.setter)(temp)) {
					if (!strct.isOptional) {
						if (Utility::tryAgain()) {
							insertC(e);
						}
						else {
							clear(e);
							return false;
						}
					}
					else {
						std::cout << "Optional field is left blank" << "\n";						
					}
				}
				
				
			}
			
		}
		
		Database db;
		std::cout << db.executeQueryD(Query<T>::insertQuery(e)) << "\n";
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
		int opt;
		std::cin >> opt;
		if (opt == 0) return true;
		if (opt < 0 || opt > map.size()) {
			if (Utility::tryAgain()) {
				deleteC(e);
			}
			else {
				return false;
			}
		}

		std::cout << "Enter " << map[opt].name << "\n";
		std::string temp;
		std::cin >> temp;
		if (!(e.*map[opt].setter)(temp)) {
			std::cout << "Invalid " << map[opt].name << " (Try Again)" << "\n";
			std::cin >> temp;
			if (!(e.*map[opt].setter)(temp)) {
				std::cout << "Entered invalid value, Sorry can't delete from Database!" << "\n";
			}


		}


		Database db;
		std::cout << db.executeQueryD(Query<T>::deleteQuery(e, map[opt])) << "\n";
		return 0;
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
			int opt;
			std::cin >> opt;
			if (opt == 0) return true;
			if (opt < 0 || opt > map.size()) {
				if (Utility::tryAgain()) {
					deleteC(e);
				}
				else {
					return false;
				}
			}

			std::cout << "Enter " << map[opt].name << "\n";
			std::string temp;
			std::cin >> temp;
			if (!(e.*map[opt].setter)(temp)) {
				std::cout << "Invalid " << map[opt].name << " (Try Again)" << "\n";
				std::cin >> temp;
				if (!(e.*map[opt].setter)(temp)) {
					std::cout << "Entered invalid value, Sorry can't view from Database!" << "\n";
				}

			}
			query = Query<T>::selectQuery(e, map[opt]);
		}
		Database db;
		std::cout << db.selectQueryD(query) << "\n";
		return 0;
		
	}

	
};
#endif