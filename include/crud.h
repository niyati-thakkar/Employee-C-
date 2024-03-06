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

static std::string whereQuery(std::string input1, std::string op1, std::string field1, std::string reln, std::string input2, std::string op2, std::string field2) {
	return std::string{ "WHERE " } + field1 + " " + op1 + " '" + input1 + "' " + reln + " " + field2 + " " + op2 + " '" + input2 + "';";
}
static std::string whereQuery(std::string input1, std::string op1, std::string field1) {
	return std::string{ "WHERE " } + field1 + " " + op1 + " '" + input1 + "';";
}
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

	static std::string advancedC(T& e) {
		std::cout << "Select the column to apply condition, Enter the number" << "\n";
		int selection1 = 0;
		int selection2 = 0;
		int op1 = 0;
		int op2 = 0;
		std::string input1;
		std::string input2;
		for (auto& [id, strct] : e.gettersetter) {
			std::cout << "Enter '"<< id <<"' to select " << strct.name << "." << "\n";
		}
		while (true) {
			std::string temp;
			std::cin >> temp;
			try {
				selection1 = std::stoi(temp);
				break;
			}
			catch (...) {
				std::cout << "Invalid Option Selected, Try Entering Again!" << "\n";
			}
		}
		
		std::cout << "Select the condition to check!, Enter the number" << "\n";
		for (auto& [id, strct] : operations) {
			std::cout << "Enter '" << id << "' to select " << strct.first << " or " << strct.second<< "." << "\n";
		}
		while (true) {
			std::string temp;
			std::cin >> temp;
			try {
				op1 = std::stoi(temp);
				break;
			}
			catch (...) {
				std::cout << "Invalid Option Selected, Try Entering Again!" << "\n";
			}
		}

		std::cout << "Enter the value to be compared!" << "\n";
		std::cin >> input1;
		std::cout << "Do you want to enter one more condition? Enter 'y' for yes and 'n' for no" << "\n";
		char c;
		std::cin >> c;
		if (c == 'y'){
			for (auto& [id, strct] : e.gettersetter) {
				std::cout << "Enter '" << id << "' to select " << strct.name << "." << "\n";
			}
			while (true) {
				std::string temp;
				std::cin >> temp;
				try {
					selection2 = std::stoi(temp);
					break;
				}
				catch (...) {
					std::cout << "Invalid Option Selected, Try Entering Again!" <<"\n";
				}
			}

			std::cout << "Select the condition to check!, Enter the number" << "\n";
			for (auto& [id, strct] : operations) {
				std::cout << "Enter '" << id << "' to select " << strct.first << " or " << strct.second << "." << "\n";
			}
			while (true) {
				std::string temp;
				std::cin >> temp;
				try {
					op2 = std::stoi(temp);
					break;
				}
				catch (...) {
					std::cout << "Invalid Option Selected, Try Entering Again!" << "\n";
				}
			}

			std::cout << "Enter the value to be compared!" << "\n";
			std::cin >> input2;
			char relatn;
			std::cout << "Enter '1' for 'and' operation i.e. both the conditions must be true for the row to be added" << "\n";
			std::cout << "Enter '2' for 'or' operation i.e. either of the condition must be true for the row to be added" << "\n";
			std::cin >> relatn;
			
			return whereQuery(input1, operations[op1].first, e.gettersetter[selection1].name, (relatn == '1' ? "AND" : "OR"), input2, operations[op2].first, e.gettersetter[selection2].name);
		}
		else {
			return whereQuery(input1, operations[op1].first, e.gettersetter[selection1].name);
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
		std::cout << "Do you want to add advanced conditions? enter 'y' for yes and 'n' for no" << "\n";
		char additionalCondition;
		std::cin >> additionalCondition;
		std::string query = selectQuery(e);
		if (additionalCondition == 'y') {
			query = query.substr(0, query.length()-1) + " " + advancedC(e);
			//std::cout << query <<"\n";
		}

		
		Database db;
		if (input == "1") {
			db.selectQueryD(query);
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