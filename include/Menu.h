#ifndef _MENU_H_
#define _MENU_H_
#include "Employee.h"
#include "Tech.h"
#include "Management.h"
#include "HR.h"
#include "Department.h"
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
		case 2: {
			CRUD<Employee>::updateC(e);
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
		int option = Utility::takeOption("Insert Department", "View Department(s)", "Update Department(s)", "Delete From Department(s)");
		if (option == 0) return;
		Department e;
		switch (option) {
		case 1: {
			CRUD<Department>::insertC(e,2);
			break;
		}
		case 2: {
			CRUD<Department>::viewC(e);
			break;
		}
		case 3: {
			CRUD<Department>::updateC(e);
			break;
		}
		case 4: {
			CRUD<Department>::deleteC(e);
			break;
		}
		}
		departmentMenu();
	}
	static void techMenu() {
		int option = Utility::takeOption("Insert Engineer(s)", "View Engineer(s)", "Update Engineer(s)", "Delete Engineer(s)");
		if (option == 0) return;
		Employee e;
		Tech t;
		switch (option) {
		case 1: {
			if (CRUD<Employee>::insertC(e, 2)) {
				t.setEmpId(e.getid());
				if (!CRUD<Tech>::insertC(t, 3)) {
					CRUD<Tech>::deleteEmp(e.getid());
					break;
				}
				Address a;
				a.setEmpId(e.getid());
				if (!CRUD<Address>::insertC(a,3)) {
					std::cout << "Address is left blank!" << "\n";
				}
			}
			
			break;
		}
		case 2: {
			CRUD<Tech>::viewC(t);
			break;
		}
		case 3: {
			CRUD<Tech>::updateC(t);
			break;
		}
		case 4: {
			CRUD<Tech>::deleteC(t);
			break;
		}
		}
		techMenu();
	}
	static void managementMenu() {
		int option = Utility::takeOption("Insert Manager(s)", "View Manager(s)", "Update Manager(s)", "Delete Manager(s)");
		if (option == 0) return;
		Employee e;
		Management m;
		switch (option) {
		case 1: {
			if (CRUD<Employee>::insertC(e, 2)) {
				m.setEmpId(e.getid());
				if (!CRUD<Management>::insertC(m, 3)) {
					CRUD<Management>::deleteEmp(e.getid());
					break;
				}
				Address a;
				a.setEmpId(e.getid());
				if (!CRUD<Address>::insertC(a, 3)) {
					std::cout << "Address is left blank!" << "\n";
				}
			}
			break;
		}
		case 2: {
			CRUD<Management>::viewC(m);
			break;
		}
		case 3: {
			CRUD<Management>::updateC(m);
			break;
		}
		case 4: {
			CRUD<Management>::deleteC(m);
			break;
		}
		}
		managementMenu();
	}
	static void HRMenu() {
		int option = Utility::takeOption("Insert HR(s)", "View HR(s)", "Update HR(s)", "Delete HR(s)");
		if (option == 0) return;
		Employee e;
		HR h;
		switch (option) {
		case 1: {
			if (CRUD<Employee>::insertC(e, 2)) {
				h.setEmpId(e.getid());
				if (!CRUD<HR>::insertC(h, 3)) {
					CRUD<HR>::deleteEmp(e.getid());
					break;
				}
				Address a;
				a.setEmpId(e.getid());
				if (!CRUD<Address>::insertC(a, 3)) {
					std::cout << "Address is left blank!" << "\n";
				}
			}
			break;
		}
		case 2: {
			CRUD<HR>::viewC(h);
			break;
		}
		case 3: {
			CRUD<HR>::updateC(h);
			break;
		}
		case 4: {
			CRUD<HR>::deleteC(h);
			break;
		}
		}
		HRMenu();
	}

};
#endif	