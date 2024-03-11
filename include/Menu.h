#ifndef _MENU_H_
#define _MENU_H_
#include "Employee.h"
#include "crud.h"
#include<iostream>

class Menu {
public:
	static void mainMenu() {
		int option = Utility::takeOption("Create New Table", "Employees", "Departments", "Management", "Tech", "HR and Finance");
		if (option == 0) exit(0);
		switch (option) {
		case 1: {
			std::cout << "create new table!";
			break;
		}
		
		case 2: {
			employeeMenu();
			break;
		}
			
		case 3: {
			departmentMenu();
			break;
		}

		case 4: {
			managementMenu();
			break;
		}

		case 5: {
			techMenu();
			break;
		}
			 
		case 6: {
			HRMenu();
			break;
		} 
		}
		mainMenu();
	}
	static void employeeMenu() {
		int option = Utility::takeOption("View Employee(s)", "Update Employee(s)", "Delete Employee(s)");
		if (option == 0) return;
		Employee e;
		switch (option) {
		case 1: {
			CRUD<Employee>::viewC(e);
			break;
		}
		case 3: {
			CRUD<Employee>::deleteC(e);
			break;
		}
		}
		employeeMenu();
	} 
	static void departmentMenu() {
		int option = Utility::takeOption("View Department(s)", "Update Department(s)", "Delete From Department(s)");
		if (option == 0) return;
	}
	static void techMenu() {
		int option = Utility::takeOption("View Engineer(s)", "Insert Engineer(s)", "Update Engineer(s)", "Delete Engineer(s)");
		if (option == 0) return;
	}
	static void managementMenu() {
		int option = Utility::takeOption("View Manager(s)", "Insert Manager(s)", "Update Manager(s)", "Delete Manager(s)");
		if (option == 0) return;
	}
	static void HRMenu() {
		int option = Utility::takeOption("View HR(s)", "Insert HR(s)", "Update HR(s)", "Delete HR(s)");
		if (option == 0) return;
	}

};
#endif	