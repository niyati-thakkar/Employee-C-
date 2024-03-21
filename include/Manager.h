#ifndef _Manager_H_
#define _Manager_H_
#include<string>
#include "Utility.h"
#include "Employee.h"
#include<map>


class Manager : public Employee {
public:

	/**********************************************************************************		getters		*************************************************************************************/

	std::string getid() const {
		if (id != 0)
			return std::to_string(id);
		return "";
	}

	std::string getManagerSpecialization() const {
		return ManagerSpecialization;
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
		return "Manager";
	}
	static size_t getLastKey() {
		return gettersetter.size() - 1;
	}

	/**********************************************************************************		setters		*************************************************************************************/


	bool setid(std::string str) {
		if (Validation::validateID(str) && str[0] == '3') {
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

	bool setManagerSpecialization(std::string str) {
		if (Validation::validateString(str)) {
			ManagerSpecialization = str;
			return true;
		}
		return false;
	}
	bool setEmpId(std::string str) {
		if (Validation::validateID(str) && str[0] == '1') {
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
		try {
			yearsOfExperience = stoi(str);
			return true;
		}
		catch (...) {
			return false;
		}
		return false;

	}


	static std::map<int, getsetmap<Manager>>& getMap() {
		return gettersetter;
	}


private:
	MID id{};
	EID empId{};
	std::string ManagerSpecialization;
	int yearsOfExperience{};
	static inline std::string TABLE_NAME = "Manager";
	inline static std::map<int, getsetmap<Manager>> gettersetter = {
		{0, getsetmap<Manager>{"EmpId",& setEmpId,& getEmpId, false }},
		{1, getsetmap<Manager>{"ID",& setid,& getid, false }},
		{2, getsetmap<Manager>{"ManagementSpecialization",& setManagerSpecialization,& getManagerSpecialization, false}},
		{3, getsetmap<Manager>{"YearsOfExperience",& setYearsOfExperience,& getYearsOfExperience, true}}
	};
};
#endif