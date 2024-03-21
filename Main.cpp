#include<iostream>
#include<string>
#include<vector>
#include <iostream>
#include "include/Menu.h"
#include "include/Utility.h"
#include "include/database.h"
#include "include/crud.h"

int main() {
	/*Employee e;
	try {
		std::cout << e.setDOB("23-01-2002") << "\n";
		std::cout << e.setDOB("23/01-2002") << "\n";
		std::cout << e.setDOB("23-01.2002") << "\n";
		std::cout << e.setDOB("23\01\2002") << "\n";
		std::cout << e.setDOB("23/01/2002") << "\n";
		std::cout << e.setDOB("53-01-2002") << "\n";
		std::cout << e.setDOB("03-03-2002") << "\n";
	}
	catch (...) {
		std::cout << "exception!" << "\n";
	}*/
	/*CRUD<Employee>::deleteC(e);
	CRUD<Employee>::viewC(e);*/
	Menu::mainMenu();
	/*Database db;
	std::vector<std::string> empids;
	db.getPrimaryKeys("select empid from employee;", empids);
	for (auto& t : empids) {
		std::cout << t << "\n";
	}*/

	/*std::cout << e.setDOB("23-01-2003");*/
	//std::cout << e.getDOB().length();
//	e.setDeptId("2000001");
//std::cout <<  e.getDeptId();


	/*std::cout << t.Employee::getTableName() << "\n";
	std::cout << t.getTableName() << "\n";*/
	//Menu::mainMenu();

}