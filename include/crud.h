#ifndef _CRUD_H_
#define _CRUD_H_
#include "Employee.h"
#include <string>
#include<optional>
#include<map>
#include "database.h"
#include "../sqlite/sqlite3.h"
#include<vector>
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	
	return 0;
}


template<typename T>
static std::string insertQuery(T e) {

	std::string fields = "";
	std::string input = "";
	for (auto& [id, strct] : e.gettersetter) {
		if (auto h = (e.*strct.getter)(); h.has_value()) {
			fields += strct.name + ", ";
			input += std::string{ "'" } + h.value_or("") + std::string{"', "};
		}
	}
	
	std::string query = "INSERT INTO " + Employee::TABLE_NAME + " (" + fields.substr(0, fields.length() - 2) + ") VALUES(" + input.substr(0, input.length() - 2) +"); ";
	std::cout << query << "\n";
	return query;
}
//template<typename T>
//static std::string deleteQuery(T e) {
//
//	std::string fields = "";
//	std::string input = "";
//	for (auto& [id, strct] : e.gettersetter) {
//		if (auto h = (e.*strct.getter)(); h.has_value()) {
//			fields += strct.name + ", ";
//			input += std::string{ "'" } + h.value_or("") + std::string{ "', " };
//		}
//	}
//
//	std::string query = "INSERT INTO " + e.TABLE_NAME + " (" + fields.substr(0, fields.length() - 2) + ") VALUES(" + input.substr(0, input.length() - 2) + "); ";
//
//	return query;
//}
template<typename T>
static std::string selectQuery(T& e, std::vector<std::string> cols) {

	std::string fields = "";
	for (auto& col : cols) {
		fields += col + ", ";
	}

	std::string query = "SELECT " + fields.substr(0,fields.length()-2) + " from " + Employee::TABLE_NAME + ";";

	return query;
}
template<typename T>
static std::string selectQuery(T& e) {
	std::string query = "SELECT * FROM " + Employee::TABLE_NAME + ";";
	return query;
}
template<typename T>
class CRUD {
private:
	inline static std::map<int, std::pair < std::string, std::string> operations;
	inline static std::string isOpt = " (Note - This field is optional. Enter '#' to keep it blank!)";
public:
	static bool insertC(T& e) {
		
		for (auto& [id, strct] : e.gettersetter) {
			while (true) {
				std::cout << "Enter " << strct.name << (strct.isOptional ? isOpt : "") << "\n";
				std::string temp;
				std::cin >> temp;
				if ((e.*strct.setter)(temp)) break;
				else if (!strct.isOptional) std::cout << "Invalid " << strct.name << " (Try Again)" << "\n";
				else {
					std::cout << "Optional field is left blank" << "\n";
					break;
				}
			}
		}
		Database db;
		std::cout << db.executeQueryD(insertQuery(e)) << "\n";
		return 0;
	}
	/*static bool deleteC(T& e) {
		while (true) {
			std::string id;
			std::cout << "Enter ID for " << e.TABLE_NAME << "\n";
			std::cin >> id;
			if (e.setid(id)) {
				break;
			}
			else {
				std::cout << "Invalid ID (try again)";
			}
		}
		
		Database db;
		std::cout << db.executeQueryD(insertQuery(e)) << "\n";
		return 0;
	}*/

	static bool advancedC(T& e) {
		std::cout << "Choose the column to apply condition, enter the number" << "\n";
		int selection = 0;
		for (auto& [id, strct] : e.gettersetter) {
			std::cout << "Enter '1' to select " << strct.name << ", '0' to discard it." << "\n";
			std::string temp;
			std::cin >> temp;
			if (temp == "1") {
				selection = id;
			}
		}
	}

	static bool viewC(T& e) {
		std::cout << "Enter '1' to View Entire Table" << "\n";
		std::cout << "Enter '2' to Select Specific Columns" << "\n";
		std::string input;
		std::cin >> input;
		std::vector<std::string> cols;
		if (input == "2") {
			for (auto& [id, strct] : e.gettersetter) {
				std::cout << "Enter '1' to select " << strct.name << ", '0' to discard it." << "\n";
				std::string temp;
				std::cin >> temp;
				if (temp == "1"){
					cols.push_back(strct.name);
				}
			}
		}
		
		Database db;
		if (input == "1") {
			db.selectQueryD(selectQuery(e));
		}
		else {
			if (cols.size() == 0) {
				std::cout << "No Columns Selected!";
				return false;
			}
			db.selectQueryD(selectQuery(e, cols));
		}
		//std::cout << db.executeQuery(insertQuery(e, "emp")) << "\n";
		
		return true;
	}
};
#endif