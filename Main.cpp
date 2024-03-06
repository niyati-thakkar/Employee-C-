#include<iostream>
#include "include/Employee.h";
#include "include/crud.h";
#include<string>
#include<vector>
int main() {
	Employee e;
	CRUD<Employee>::viewC(e);
}