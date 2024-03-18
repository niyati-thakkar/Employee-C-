#ifndef _MANAGEMENT_H_
#define _MANAGEMENT_H_
#include<string>
#include "Utility.h"
#include "Employee.h"
#include<map>


class Management : public Employee {
public:
	std::string getid() const {
		if (Validation::validateID(std::to_string(id)))
			return std::to_string(id);
		return "";
	}

	std::string getManagementSpecialization() const {
		return managementSpecialization;
	}
	std::string getYearsOfExperience() const {
		if (yearsOfExperience != 0)
			return std::to_string(yearsOfExperience);
		return "";
	}
	std::string getEmpId() const {
		if (empId != 0)
			return std::to_string(empId);
		return "";
	}
	static bool isKeyPresent(std::string table, std::string col, std::string val) {
		Database db;
		return db.valueExistsInTable(table, col, val);

	}

	bool deleteEmp(std::string id) {
		Database db;
		std::cout << db.executeQueryD(std::string{ "DELETE FROM EMPLOYEE WHERE ID = '" } + id + "';") << "\n";
		return true;
	}
	static std::string getTableName() {
		return "Management";
	}
	static size_t getLastKey() {
		return gettersetter.size() - 1;
	}

	bool setid(std::string str) {
		if (Validation::validateID(str)) {
			try {
				id = stoi(str);
				return true;
			}
			catch (...) {
				return false;
			}
		}
		return false;

	}

	bool setManagementSpecialization(std::string str) {
		if (Validation::validateString(str)) {
			managementSpecialization = str;
			return true;
		}
		return false;
	}
	bool setEmpId(std::string str) {
		if (Validation::validateID(str)) {
			try {
				empId = stoi(str);
				if (CRUD::isKeyPresent("Employee", "EmpId", str)) {
					return true;
				}
				else {
					std::cout << "Employee with given ID doesn't exists!" << "\n";
				}

			}
			catch (...) {
				return false;
			}
		}
		return false;
	}
	bool setYearsOfExperience(std::string str) {
		if (Validation::validateID(str)) {
			try {
				yearsOfExperience = stoi(str);
				return true;
			}
			catch (...) {
				return false;
			}
		}
		return false;

	}


	static std::map<int, getsetmap<Management>>& getMap() {
		return gettersetter;
	}


private:
	MID id{};
	EID empId{};
	std::string managementSpecialization;
	int yearsOfExperience{};

	inline static std::map<int, getsetmap<Management>> gettersetter = {
		{0, getsetmap<Management>{"EmpId",& setEmpId,& getEmpId, false }},
		{1, getsetmap<Management>{"ID",& setid,& getid, false }},
		{2, getsetmap<Management>{"ManagementSpecialization",& setManagementSpecialization,& getManagementSpecialization, false}},
		{3, getsetmap<Management>{"YearsOfExperience",& setYearsOfExperience,& getYearsOfExperience, true}}
	};
};
#endif