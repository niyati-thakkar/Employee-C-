#ifndef _DATABASE_H_
#define _DATABASE_H_
#include<iostream>
#include<string>
#include "Log.h"
#include "../sqlite/sqlite3.h"
class Database {
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	Lognspace::Log logger{ Lognspace::Log::Level::LevelInfo, "EmployeeDatabase.txt"};

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
			logger.Info("Database opened successfully");
		}
	}
	~Database() {
		sqlite3_close(db);
	}
	bool executeQueryD(std::string query) {
		const char* sqlq = query.c_str();
		rc = sqlite3_exec(db, sqlq, callback, 0, &zErrMsg);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: \n" << zErrMsg;
			sqlite3_free(zErrMsg);
		}
		else {
			//std::cout << sqlite3_last_insert_rowid(db) << "\n";
			logger.Info("Query Executed successfully");
			return true;
		}
		logger.Error("Query failed!");
		return false;
	}
	bool selectQueryD(std::string query) {
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
			logger.Info("Operation done successfully");
			return true;
		}
		logger.Error("Query failed!");
		return false;
		
	}
	static int valueExistsCallback(void* exists, int argc, char** argv, char** azColName) {
		int* result = static_cast<int*>(exists);
		*result = (argc > 0 && argv[0] != nullptr);
		return 0;
	}

	bool valueExistsInTable(const std::string& tableName, const std::string& value) {
		std::string query = "SELECT 1 FROM " + tableName + " WHERE id = '" + value + "';";

		char* zErrMsg = nullptr;
		int exists = 0;

		int rc = sqlite3_exec(db, query.c_str(), valueExistsCallback, &exists, &zErrMsg);

		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			return false; // Consider returning an error indicator or throwing an exception
		}

		return (exists == 1);
	}

	int lastInsertedValue() {
		const char* query = "SELECT last_insert_rowid();";
		int lastID = -1; // Initialize with a default value

		rc = sqlite3_exec(db, query, [](void* data, int argc, char** argv, char** azColName) -> int {
			if (argc > 0 && argv[0] != nullptr) {
				*static_cast<int*>(data) = std::stoi(argv[0]);
			}
			return 0;
			}, &lastID, &zErrMsg);

		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}

		return lastID;
	}
};
#endif
