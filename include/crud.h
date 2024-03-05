#ifndef _CRUD_H_
#define _CRUD_H_
#include "Employee.h"
#include "../sqlite/sqlite3.h"
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}
class CRUD {
public:
	static bool insert(Employee& e) {
		for (auto& [id, strct] : e.gettersetter) {
			std::cout << "Enter " << strct.name << "\n";
			std::string temp;
			std::cin >> temp;
			(e.*strct.setter)(temp);
			std::cout << (e.*strct.getter)()<<"\n";
		}
		return 0;
		/*sqlite3* db;
		char* zErrMsg = 0;
		int rc = sqlite3_open("Employee.db", &db);
		if (rc) {
			std::cerr << "cant open db";
			return 0;
		}
		else {
			std::cout << " database opened successfully";
		}
		std::string str = "INSERT INTO EMPLOYEE(EmpID, Fname, Lname, ContactNumber, Email, DOB, JoiningDate, BranchID, JobID, ReportingManager, DocumentFolder) VALUES (" + std::to_string(e.EmpID) + ", '" + e.Fname + "', '" + e.Lname + "', '" + e.ContactNumber + "', '" + e.Email + "'," + e.DOB + ", " + e.JoiningDate + ", " + std::to_string(e.BranchID) + ", " + std::to_string(e.JobID) + ", " + std::to_string(e.ReportingManager) + ", '" + e.DocumentFolder + "' )";
		std::string addr = "INSERT INTO ADDRESS VALUES(" + std::to_string(e.EmpID) + ", " + std::string{ "'" } + e.EmpAddress.Location + "', '" + e.EmpAddress.City + "', '" + e.EmpAddress.State + "', '" + e.EmpAddress.Country + "'," + std::to_string(e.EmpAddress.Pincode) + ")";

		std::cout << str << "\n";
		const char* sqlq = str.c_str();
		rc = sqlite3_exec(db, sqlq, callback, 0, &zErrMsg);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: \n" << zErrMsg;
			sqlite3_free(zErrMsg);
		}
		else {
			std::cout << "Table created successfully\n";
		}*/
	}
};
#endif