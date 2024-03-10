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
	
	//static std::string deleteQuery(T e) {
	//	return std::string{ "DELETE FROM " } + T::TABLE_NAME + " WHERE ID = " + e.getid().value_or("") + ";";
	//}

	//
	//static std::string deleteQuery(T e, std::string query) {
	//	return std::string{ "DELETE FROM " } + T::TABLE_NAME + " " + query;
	//}

	//static std::string whereQuery(std::string input1, std::string op1, std::string field1, std::string reln, std::string input2, std::string op2, std::string field2) {
	//	return std::string{ "WHERE " } + field1 + " " + op1 + " '" + input1 + "' " + reln + " " + field2 + " " + op2 + " '" + input2 + "';";
	//}
	//static std::string whereQuery(std::string input1, std::string op1, std::string field1) {
	//	return std::string{ "WHERE " } + field1 + " " + op1 + " '" + input1 + "';";
	//}
	
	//static std::string selectQuery(T& e, std::vector<std::string> cols) {

	//	std::string fields = "";
	//	for (auto& col : cols) {
	//		fields += col + ", ";
	//	}

	//	std::string query = "SELECT " + fields.substr(0, fields.length() - 2) + " from " + T::TABLE_NAME + ";";

	//	return query;
	//}

	//static std::string selectQuery(T& e) {
	//	std::string query = "SELECT * FROM " + Employee::TABLE_NAME + ";";
	//	return query;
	//}
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
	static bool tryAgain() {
		std::cout << "The entered value is not valid. Do you wish to try again?\n1. YES\n2. NO, Go Back to previous Menu!";
		int opt;
		std::cin >> opt;
		return opt == 1 ? true : false;
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
						if (tryAgain()) {
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
	//static bool deleteC(T& e) {
	//	std::cout << "Enter '1' to delete a row based on ID";
	//	std::cout << "Enter '2' for Advanced Delete";
	//	char opt;
	//	std::string query;
	//	std::cin >> opt;
	//	while (true) {
	//		if (opt == '1') {
	//			std::cout << "Enter ID" << "\n";
	//			while (true) {
	//				try {
	//					std::string temp;
	//					std::cin >> temp;
	//					e.setid(temp);
	//					break;
	//				}
	//				catch (...) {
	//					std::cout << "Invalid ID please Try again!" << "\n";
	//				}
	//			}
	//			query = deleteQuery(e);
	//			break;
	//		}
	//		else if (opt == '2') {
	//			query = advancedC(e);
	//			query = deleteQuery(e, query);
	//			break;
	//		}
	//		else {
	//			std::cout << "Invalid Option selected, please try again!" << "\n";
	//		}
	//	}
	//	
	//	Database db;
	//	std::cout << db.executeQueryD(deleteQuery(e)) << "\n";
	//	return 0;
	//}

	//static std::string advancedC(T& e) {
	//	std::cout << "Select the column to apply condition, Enter the number" << "\n";
	//	int selection1 = 0;
	//	int selection2 = 0;
	//	int op1 = 0;
	//	int op2 = 0;
	//	std::string input1;
	//	std::string input2;
	//	for (auto& [id, strct] : e.gettersetter) {
	//		std::cout << "Enter '"<< id <<"' to select " << strct.name << "." << "\n";
	//	}
	//	while (true) {
	//		std::string temp;
	//		std::cin >> temp;
	//		try {
	//			selection1 = std::stoi(temp);
	//			break;
	//		}
	//		catch (...) {
	//			std::cout << "Invalid Option Selected, Try Entering Again!" << "\n";
	//		}
	//	}
	//	
	//	std::cout << "Select the condition to check!, Enter the number" << "\n";
	//	for (auto& [id, strct] : operations) {
	//		std::cout << "Enter '" << id << "' to select " << strct.first << " or " << strct.second<< "." << "\n";
	//	}
	//	while (true) {
	//		std::string temp;
	//		std::cin >> temp;
	//		try {
	//			op1 = std::stoi(temp);
	//			break;
	//		}
	//		catch (...) {
	//			std::cout << "Invalid Option Selected, Try Entering Again!" << "\n";
	//		}
	//	}

	//	std::cout << "Enter the value to be compared!" << "\n";
	//	std::cin >> input1;
	//	std::cout << "Do you want to enter one more condition? Enter 'y' for yes and 'n' for no" << "\n";
	//	char c;
	//	std::cin >> c;
	//	if (c == 'y'){
	//		for (auto& [id, strct] : e.gettersetter) {
	//			std::cout << "Enter '" << id << "' to select " << strct.name << "." << "\n";
	//		}
	//		while (true) {
	//			std::string temp;
	//			std::cin >> temp;
	//			try {
	//				selection2 = std::stoi(temp);
	//				break;
	//			}
	//			catch (...) {
	//				std::cout << "Invalid Option Selected, Try Entering Again!" <<"\n";
	//			}
	//		}

	//		std::cout << "Select the condition to check!, Enter the number" << "\n";
	//		for (auto& [id, strct] : operations) {
	//			std::cout << "Enter '" << id << "' to select " << strct.first << " or " << strct.second << "." << "\n";
	//		}
	//		while (true) {
	//			std::string temp;
	//			std::cin >> temp;
	//			try {
	//				op2 = std::stoi(temp);
	//				break;
	//			}
	//			catch (...) {
	//				std::cout << "Invalid Option Selected, Try Entering Again!" << "\n";
	//			}
	//		}

	//		std::cout << "Enter the value to be compared!" << "\n";
	//		std::cin >> input2;
	//		char relatn;
	//		std::cout << "Enter '1' for 'and' operation i.e. both the conditions must be true for the row to be added" << "\n";
	//		std::cout << "Enter '2' for 'or' operation i.e. either of the condition must be true for the row to be added" << "\n";
	//		std::cin >> relatn;
	//		
	//		return whereQuery(input1, operations[op1].first, e.gettersetter[selection1].name, (relatn == '1' ? "AND" : "OR"), input2, operations[op2].first, e.gettersetter[selection2].name);
	//	}
	//	else {
	//		return whereQuery(input1, operations[op1].first, e.gettersetter[selection1].name);
	//	}


	//}

	//static bool viewC(T& e) {
	//	std::cout << "Enter '1' to View Entire Table" << "\n";
	//	std::cout << "Enter '2' to Select Specific Columns" << "\n";
	//	std::string input;
	//	std::cin >> input;
	//	std::vector<std::string> cols;
	//	std::string query;
	//	while (true) {
	//		if (input == "1") {
	//			query = selectQuery(e);
	//			break;
	//		}
	//		if (input == "2") {
	//			for (auto& [id, strct] : e.gettersetter) {
	//				std::cout << "Enter '1' to select " << strct.name << ", '0' to discard it." << "\n";
	//				std::string temp;
	//				std::cin >> temp;
	//				if (temp == "1") {
	//					cols.push_back(strct.name);
	//				}
	//			}
	//			if (cols.size() == 0) {
	//				std::cout << "No Columns Selected!";
	//				continue;
	//			}
	//			query = selectQuery(e, cols);
	//			break;
	//		}
	//		std::cout << "invalid option selected please try again!" << "\n";
	//	}
	//	
	//	
	//	std::cout << "Do you want to add advanced conditions? enter 'y' for yes and 'n' for no" << "\n";
	//	char additionalCondition;
	//	std::cin >> additionalCondition;
	//	if (additionalCondition == 'y') {
	//		query = query.substr(0, query.length()-1) + " " + advancedC(e);
	//		//std::cout << query <<"\n";
	//	}

	//	
	//	Database db;
	//	db.selectQueryD(query);
	//	//std::cout << db.executeQuery(insertQuery(e, "emp")) << "\n";
	//	
	//	return true;
	//}
};
#endif