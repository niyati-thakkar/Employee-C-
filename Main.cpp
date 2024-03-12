#include<iostream>
#include<string>
#include<vector>
#include <iostream>
#include "include/Menu.h"
#include "include/Utility.h"

#include "include/crud.h"

int main() {
	Employee e;
	/*CRUD<Employee>::deleteC(e);
	CRUD<Employee>::viewC(e);*/
	Menu::mainMenu();
	/*std::cout << e.setDOB("23-01-2003");*/
	//std::cout << e.getDOB().length();
//	e.setDeptId("2000001");
//std::cout <<  e.getDeptId();
}