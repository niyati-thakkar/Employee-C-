#ifndef _MENU_H_
#define _MENU_H_
#include "Employee.h"

#include "Engineer.h"

#include "Manager.h"

#include "HR.h"

#include "Department.h"

#include "crud.h"

#include<iostream>

namespace Menu {

	void employeeMenu() {
		bool whileFlag = true;
		do {
			int option = Utility::takeOption(true, "Insert Employee(s)", "View Employee(s)", "Update Employee(s)", "Delete Employee(s)");
			if (option == 0) return;
			Employee e;
			switch (option) {
			case 1: {
				CRUD::insert<Employee>(e);
				break;
			}
			case 2: {
				CRUD::view<Employee>(e);
				break;
			}
			case 3: {
				CRUD::update<Employee>(e);
				break;
			}
			case 4: {
				CRUD::removeEmpl<Employee>(e);
				break;
			}
			}
		} while (whileFlag);
	}
	void departmentMenu() {
		bool whileFlag = true;
		do {
			int option = Utility::takeOption(true, "Insert Department", "View Department(s)", "Update Department(s)", "Delete From Department(s)");
			if (option == 0) return;
			Department e;
			switch (option) {
			case 1: {
				CRUD::insert<Department>(e);
				break;
			}
			case 2: {
				CRUD::view<Department>(e);
				break;
			}
			case 3: {
				CRUD::update<Department>(e);
				break;
			}
			case 4: {
				CRUD::removeDept<Department>(e);
				break;
			}
			}
		} while (whileFlag);
	}
	void EngineerMenu() {
		bool whileFlag = true;
		do {
			int option = Utility::takeOption(true, "Insert Engineer(s)", "View Engineer(s)", "Update Engineer(s)", "Delete Engineer(s)");
			if (option == 0) return;
			Engineer t;
			switch (option) {
			case 1: {
				CRUD::insertC<Employee, Engineer>(t);
				break;
			}
			case 2: {
				CRUD::viewC<Employee, Engineer>(t);
				break;
			}
			case 3: {
				CRUD::updateC<Employee, Engineer>(t);
				break;
			}
			case 4: {
				CRUD::removeEmplC<Employee, Engineer>(t);
				break;
			}
			}
		} while (whileFlag);
	}
	void ManagerMenu() {
		bool whileFlag = true;
		do {
			int option = Utility::takeOption(true, "Insert Manager(s)", "View Manager(s)", "Update Manager(s)", "Delete Manager(s)");
			if (option == 0) return;
			Employee e;
			Manager m;
			switch (option) {
			case 1: {
				CRUD::insertC<Employee, Manager>(m);
				break;
			}
			case 2: {
				CRUD::viewC<Employee, Manager>(m);
				break;
			}
			case 3: {
				CRUD::updateC<Employee, Manager>(m);
				break;
			}
			case 4: {
				CRUD::removeEmplC<Employee, Manager>(m);
				break;
			}
			}
		} while (whileFlag);
	}
	void HRMenu() {
		bool whileFlag = true;
		do {
			int option = Utility::takeOption(true, "Insert HR(s)", "View HR(s)", "Update HR(s)", "Delete HR(s)");
			if (option == 0) return;
			Employee e;
			HR h;
			switch (option) {
			case 1: {
				CRUD::insertC<Employee, HR>(h);
				break;
			}
			case 2: {
				CRUD::viewC<Employee, HR>(h);
				break;
			}
			case 3: {
				CRUD::updateC<Employee, HR>(h);
				break;
			}
			case 4: {
				CRUD::removeEmplC<Employee, HR>(h);
				break;
			}
			}
		} while (whileFlag);
	}
	void mainMenu() {
		bool whileFlag = true;
		do {
			int option = Utility::takeOption(true, "Create New Table", "Employees", "Departments", "Manager", "Engineer", "HR and Finance");
			if (option == 0) return;
			switch (option) {
			case 0: {
				whileFlag = false;
				break;
			}
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
				ManagerMenu();
				break;
			}

			case 5: {
				EngineerMenu();
				break;
			}

			case 6: {
				HRMenu();
				break;
			}
			}

		} while (whileFlag);
	}

};
#endif