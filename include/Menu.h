#ifndef _MENU_H_
#define _MENU_H_
#include "Employee.h"

#include "Tech.h"

#include "Management.h"

#include "HR.h"

#include "Department.h"

#include "crud.h"

#include<iostream>

namespace Menu {

    void employeeMenu() {
        bool whileFlag = true;
        do {
            int option = Utility::takeOption("View Employee(s)", "Update Employee(s)", "Delete Employee(s)");
            if (option == 0) return;
            Employee e;
            switch (option) {
            case 1: {
                CRUD::view(e);
                break;
            }
            case 2: {
                CRUD::update(e);
                break;
            }
            case 3: {
                CRUD::remove(e);
                break;
            }
            }
        } while (whileFlag);
    }
    void departmentMenu() {
        bool whileFlag = true;
        do {
            int option = Utility::takeOption("Insert Department", "View Department(s)", "Update Department(s)", "Delete From Department(s)");
            if (option == 0) return;
            Department e;
            switch (option) {
            case 1: {
                CRUD::insert(e);
                break;
            }
            case 2: {
                CRUD::view(e);
                break;
            }
            case 3: {
                CRUD::update(e);
                break;
            }
            case 4: {
                CRUD::remove(e);
                break;
            }
            }
        } while (whileFlag);
    }
    void techMenu() {
        bool whileFlag = true;
        do {
            int option = Utility::takeOption("Insert Engineer(s)", "View Engineer(s)", "Update Engineer(s)", "Delete Engineer(s)");
            if (option == 0) return;
            Tech t;
            switch (option) {
            case 1: {
                CRUD::insertC(t);
                break;
            }
            case 2: {
                CRUD::viewC(t);
                break;
            }
            case 3: {
                CRUD::update(t);
                break;
            }
            case 4: {
                CRUD::remove(t);
                break;
            }
            }
        } while (whileFlag);
    }
    void managementMenu() {
        bool whileFlag = true;
        do {
            int option = Utility::takeOption("Insert Manager(s)", "View Manager(s)", "Update Manager(s)", "Delete Manager(s)");
            if (option == 0) return;
            Employee e;
            Management m;
            switch (option) {
            case 1: {
                CRUD::insertC(m);
                break;
            }
            case 2: {
                CRUD::viewC(m);
                break;
            }
            case 3: {
                CRUD::update(m);
                break;
            }
            case 4: {
                CRUD::remove(m);
                break;
            }
            }
        } while (whileFlag);
    }
    void HRMenu() {
        bool whileFlag = true;
        do {
            int option = Utility::takeOption("Insert HR(s)", "View HR(s)", "Update HR(s)", "Delete HR(s)");
            if (option == 0) return;
            Employee e;
            HR h;
            switch (option) {
            case 1: {
                CRUD::insertC(h);
                break;
            }
            case 2: {
                CRUD::viewC(h);
                break;
            }
            case 3: {
                CRUD::update(h);
                break;
            }
            case 4: {
                CRUD::remove(h);
                break;
            }
            }
        } while (whileFlag);
    }
    void mainMenu() {
        bool whileFlag = true;
        do {
            int option = Utility::takeOption("Create New Table", "Employees", "Departments", "Management", "Tech", "HR and Finance");
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

        } while (whileFlag);
    }

};
#endif