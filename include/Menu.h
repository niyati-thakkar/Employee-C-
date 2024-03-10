#ifndef _MENU_H_
#define _MENU_H_
#include "Employee.h"
#include "crud.h"
#include<iostream>

class Menu {
	static inline std::string backMessage = "0. Go back to previous menu!";
	static inline std::string exitMessage = "100. To exit!";
public:
	static void mainMenu() {
		int option = takeOption("Create New Table", "Employees", "Departments", "Management", "Tech", "HR and Finance");
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
		int option = takeOption("View Employee(s)", "Update Employee(s)", "Delete Employee(s)");
		if (option == 0) return;
		Employee e;
		switch (option) {
		case 1: {
			CRUD<Employee>::insertC(e);
		}
		}
	} 
	static void departmentMenu() {
		int option = takeOption("View Department(s)", "Update Department(s)", "Delete From Department(s)");
		if (option == 0) return;
	}
	static void techMenu() {
		int option = takeOption("View Engineer(s)", "Insert Engineer(s)", "Update Engineer(s)", "Delete Engineer(s)");
		if (option == 0) return;
	}
	static void managementMenu() {
		int option = takeOption("View Manager(s)", "Insert Manager(s)", "Update Manager(s)", "Delete Manager(s)");
		if (option == 0) return;
	}
	static void HRMenu() {
		int option = takeOption("View HR(s)", "Insert HR(s)", "Update HR(s)", "Delete HR(s)");
		if (option == 0) return;
	}

	template<typename ...Args>
	[[nodiscard]] static int takeOption(Args ...args) { 
		std::cout << backMessage << "\n";
		int i = 1;
		((std::cout << i++ << ". " << std::forward<Args>(args) << " \n"), ...);
		std::cout << exitMessage << "\n";
		int option;
		std::cin >> option;
		if (option == 100) {
			exit(0);
		}
		if (option < 0 || option >= i) {
			std::cout << "Please enter a valid option" << "\n";
			std::cin >> option;
		}
		if (option < 0 || option >= i) {
			std::cout << "Invalid Option Selected!" << "\n";
			return 0;
		}
		return option;
		 
	}
};
#endif	