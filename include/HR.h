#ifndef _HR_H_
#define _HR_H_
#include<string>
#include "Utility.h"
#include "Employee.h"
#include<map>


class HR : public Employee {
public:
	/**********************************************************************************		getters		*************************************************************************************/

	std::string getid() const {
		if (id != 0)
			return std::to_string(id);
		return "";
	}
	std::string getEmpId() const {
		if (empId != 0)
			return std::to_string(empId);
		return "";
	}
	std::string getProficientLangugae() const {
		return proficientLangugae;
	}
	std::string getRecruitingExperience() const {
		if (recruitingExperience != 0)
			return std::to_string(recruitingExperience);
		return "";
	}


	static std::string getTableName() {
		return TABLE_NAME;
	}
	static std::map<int, getsetmap<HR>>& getMap() {
		return gettersetter;
	}
	static size_t getLastKey() {
		return gettersetter.size() - 1;
	}

	/**********************************************************************************		setters		*************************************************************************************/

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

	bool setid(std::string str) {
		if (Validation::validateID(str) && str[0] == '5') {
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

	bool setProficientLangugae(std::string str) {
		if (Validation::validateString(str)) {
			proficientLangugae = str;
			return true;
		}
		return false;
	}

	bool setRecruitingExperience(std::string str) {
		try {
			recruitingExperience = stoi(str);
			return true;
		}
		catch (...) {
			return false;
		}
		return false;

	}
	double calculateSalary() override {
		try {
			double yoe = std::stod(getYearsOfExperience());
			double basesalary = std::stod(getBaseSalary());
			return Employee::calculateSalary() + yoe * yoeBonus * basesalary / 100;
		}
		catch (...) {
			return 0;
		}

	}

private:
	HID id{};
	EID empId{};
	std::string proficientLangugae;
	int recruitingExperience{};
	inline static double yoeBonus = 8.0;
	inline static std::string TABLE_NAME = "HR";
	inline static std::map<int, getsetmap<HR>> gettersetter = {
		{0, getsetmap<HR>{"EmpId",& setEmpId,& getEmpId, false }},
		{1, getsetmap<HR>{"ID",& setid,& getid, false }},
		{2, getsetmap<HR>{"ProficientLanguage",& setProficientLangugae,& getProficientLangugae, false}},
		{3, getsetmap<HR>{"RecruitingExperience",& setRecruitingExperience,& getRecruitingExperience, true}}
	};
};
#endif