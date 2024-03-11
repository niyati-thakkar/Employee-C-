#ifndef _DATABASE_H_
#define _DATABASE_H_
#include<iostream>
#include<string>
#include "../sqlite/sqlite3.h"
class Database {
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
public:
	static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
		int i;
		for (i = 0; i < argc; i++) {
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		}
		printf("\n");
		return 0;
	}
	Database() {
		rc = sqlite3_open("Employee.db", &db);
		if (rc) {
			std::cerr << "can't open db" << "\n";
			return;
		}
		else {
			std::cout << " database opened successfully" << "\n";
		}
	}
	~Database() {
		sqlite3_close(db);
	}
	std::string executeQueryD(std::string query) {
		const char* sqlq = query.c_str();
		rc = sqlite3_exec(db, sqlq, callback, 0, &zErrMsg);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: \n" << zErrMsg;
			sqlite3_free(zErrMsg);
		}
		else {
			return "Query Executed successfully\n";
		}
	}
	std::string selectQueryD(std::string query) {
		/* Create SQL statement */
		/* Create SQL statement */
		const char* sql = query.c_str();

		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			return "Operation done successfully\n";
		}
		
	}
};
#endif
