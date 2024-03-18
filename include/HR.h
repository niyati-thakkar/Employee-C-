#ifndef _HR_H_
#define _HR_H_
#include<string>
#include "Utility.h"
#include "Employee.h"
#include<map>


class HR : public Employee {
public:
	std::string getid() const {
		if (Validation::validateID(std::to_string(id)))
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
		return "HR";
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

	bool setProficientLangugae(std::string str) {
		if (Validation::validateString(str)) {
			proficientLangugae = str;
			return true;
		}
		return false;
	}

	bool setRecruitingExperience(std::string str) {
		if (Validation::validateID(str)) {
			try {
				recruitingExperience = stoi(str);
				return true;
			}
			catch (...) {
				return false;
			}
		}
		return false;

	}
	static std::map<int, getsetmap<HR>>& getMap() {
		return gettersetter;
	}
	static size_t getLastKey() {
		return gettersetter.size() - 1;
	}

private:
	HID id{};
	EID empId{};
	std::string proficientLangugae;
	int recruitingExperience{};
	inline static std::map<int, getsetmap<HR>> gettersetter = {
		{1, getsetmap<HR>{"ID",& setid,& getid, false }},
		{2, getsetmap<HR>{"EmpId",& setEmpId,& getEmpId, false }},
		{3, getsetmap<HR>{"ProficientLangugae",& setProficientLangugae,& getProficientLangugae, false}},
		{4, getsetmap<HR>{"RecruitingExperience",& setRecruitingExperience,& getRecruitingExperience, true}}
	};
};
#endif