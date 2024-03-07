#include<iostream>
#include "include/Employee.h"
#include "include/crud.h"
#include<string>
#include<vector>
#include <iostream>
int main(){
// Print a red string
std::cout << osm::feat(osm::col, "red") << "This string is red!" << osm::feat(osm::rst, "color");

// Print a bold string
std::cout << osm::feat(osm::sty, "red") << "This string is bold!" << osm::feat(osm::rst, "bd/ft");
}
//int main() {
//	Employee e;
//	CRUD<Employee>::deleteC(e);
//	CRUD<Employee>::viewC(e);
//}