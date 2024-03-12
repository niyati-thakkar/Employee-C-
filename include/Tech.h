#ifndef _TECH_H_
#define _TECH_H_
#include<string>
#include "Utility.h"
#include "Employee.h"
#include<map>


class Tech : public Employee{
public:
	std::string getid() const {
		if (Validation::validateID(std::to_string(id)))
			return std::to_string(id);
		return "";
	}

	std::string getTechSpecialization() const {
		return techSpecialization;
	}
	
	std::string getCurrentProject() const {
		return currentProject;
	}
	std::string getTableName() const {
		return "Tech";
	}
	std::string getEmpId() const {
		if (empId != 0)
			return std::to_string(empId);
		return "";
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

	bool setTechSpecialization(std::string str) {
		if (Validation::validateString(str)) {
			techSpecialization = str;
			return true;
		}
		return false;
	}

	bool setEmpId(std::string str) {
		if (Validation::validateID(str)) {
			try {
				empId = stoi(str);
				if (CRUD<Employee>::isKeyPresent("Employee", str)) {
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
	bool setCurrentProject(std::string str) {
		if (Validation::validateString(str)) {
			currentProject = str;
			return true;
		}
		return false;
	}
	std::map<int, getsetmap<Tech>>& getMap() const {
		return gettersetter;
	}


private:
	TID id;
	EID empId;
	std::string techSpecialization;
	std::string currentProject;
	
	inline static std::map<int, getsetmap<Tech>> gettersetter = {
		{1, getsetmap<Tech>{"ID",& setid,& getid, false }},
		{2, getsetmap<Tech>{"EmpId",& setEmpId,& getEmpId, false }},
		{3, getsetmap<Tech>{"TechSpecialization",& setTechSpecialization,& getTechSpecialization, false}},
		{4, getsetmap<Tech>{"CurrentProject",& setCurrentProject,& getCurrentProject, true}}
	};
};
#endif