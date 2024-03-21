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

public:

	inline static Lognspace::Log logger{ Lognspace::Log::Level::LevelInfo, "EmployeeDatabase.txt" };
	static int callback(void* count, int argc, char** argv, char** azColName) {
		// Calculate the maximum width of column names and values
		int* cnt = static_cast<int*>(count);
		*cnt = *cnt + 1;
		int maxColumnNameWidth = 30;
		int maxColumnValueWidth = 60;
		
		int totalWidth = maxColumnNameWidth + maxColumnValueWidth + 5;
		// Print top border
		std::cout << "+";

		// Print the separator line using a loop
		for (int i = 0; i < totalWidth; i++) {
			std::cout << "-";
		}

		// Print a space and the second '+'
		std::cout << "+" << std::endl;
		std::cout << std::setfill(' ');

		// Print table
		for (int i = 0; i < argc; ++i) {
			
			std::cout << "| " << std::left << std::setw(maxColumnNameWidth) << azColName[i] << " | ";
			std::cout << std::setw(maxColumnValueWidth) << (argv[i] ? argv[i] : "-") << " |" << std::endl;
		}

		// Print bottom border
		// Calculate total width (including padding)
		 // 4 for two '+' and two spaces

		// Print the first '+'
		std::cout << "+";

		// Print the separator line using a loop
		for (int i = 0; i < totalWidth; i++) {
			std::cout << "-";
		}

		// Print a space and the second '+'
		std::cout << "+" << std::endl;
		std::cout << std::setfill(' ');

		return 0;
	}

	Database() {
		rc = sqlite3_open("Employee.db", &db);
		if (rc) {
			std::cerr << "can't open db" << "\n";
			return;
		}
		else {
			sqlite3_exec(db, "PRAGMA case_sensitive_like = ON;", callback, 0, &zErrMsg);
		}
	}
	~Database() {
		sqlite3_close(db);
	}
	bool executeQueryD(std::string query) {
		const char* sqlq = query.c_str();
		rc = sqlite3_exec(db, sqlq, callback, 0, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			//std::cout << sqlite3_last_insert_rowid(db) << "\n";
			if (sqlite3_changes(db) == 0) {
				logger.Warn("No records Affected!");
			}
			return true;
		}
		return false;
	}
	bool selectQueryD(std::string query) {
		/* Create SQL statement */
		/* Create SQL statement */
		const char* sql = query.c_str();
		int count = 0;
		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, callback, &count, &zErrMsg);

		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			return false;
		}
		else {
			if (count == 0) {
				logger.Warn("No Records Found.");
				return false;
			}
			return true;
		}
		
		

	}
	static int valueExistsCallback(void* exists, int argc, char** argv, char** azColName) {
		int* result = static_cast<int*>(exists);
		*result = (argc > 0 && argv[0] != nullptr);
		return 0;
	}

	bool valueExistsInTable(const std::string& tableName, const std::string& col, const std::string& value) {
		std::string query = "SELECT 1 FROM " + tableName + " WHERE " + col + " = '" + value + "'; ";

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

	std::string getColValue(const std::string& tableName, const std::string& columnName, const std::string& primaryKey, const std::string& columnToFetch) {
		sqlite3_stmt* stmt;
		std::string result;

		
		// Prepare SQL statement
		std::string sql = "SELECT " + columnToFetch + " FROM " + tableName + " WHERE " + columnName + " = ?;";
		rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_close(db);
			return "";
		}

		// Bind primary key parameter
		rc = sqlite3_bind_text(stmt, 1, primaryKey.c_str(), -1, SQLITE_STATIC);
		if (rc != SQLITE_OK) {
			std::cerr << "Failed to bind parameter: " << sqlite3_errmsg(db) << std::endl;
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return "";
		}

		// Execute the statement
		rc = sqlite3_step(stmt);
		if (rc == SQLITE_ROW) {
			// Retrieve the value from the result set
			const unsigned char* colValue = sqlite3_column_text(stmt, 0);
			if (colValue)
				result = reinterpret_cast<const char*>(colValue);
		}
		else if (rc == SQLITE_DONE) {
			std::cerr << "No rows returned." << std::endl;
		}
		else {
			std::cerr << "Error fetching row: " << sqlite3_errmsg(db) << std::endl;
		}

		// Finalize and close
		sqlite3_finalize(stmt);
		sqlite3_close(db);

		return result;
	}
	bool turnCascadeOn() {
		rc = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", callback, 0, &zErrMsg);
		return rc == SQLITE_OK;
	}
	bool turnCascadeOff() {
		rc = sqlite3_exec(db, "PRAGMA foreign_keys = OFF;", callback, 0, &zErrMsg);
		return rc == SQLITE_OK;
	}
	bool getPrimaryKeys(std::string query, std::vector<std::string>& empids) {
		rc = sqlite3_exec(db, query.c_str(), [](void* data, int argc, char** argv, char** azColName) -> int {
			std::vector<std::string>* empids = static_cast<std::vector<std::string>*>(data);
			for (int i = 0; i < argc; i++) {
				empids->push_back(argv[i]); // Assuming primary key is the first (and only) column in the result
			}
			return 0;
			}, &empids, &zErrMsg);

		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			sqlite3_close(db);
			return false;
		}

		// Close the database connection
		sqlite3_close(db);

		return true;
	}

};
#endif
