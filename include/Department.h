#ifndef _DEPARTMENT_H_
#define _DEPARTMENT_H_
#include<string>
#include "Utility.h"
#include<map>


class Department {
public:
	std::string getid() const{
		if (Validation::validateID(std::to_string(id)))
			return std::to_string(id);
		return "";
	}

	std::string getDeptName() const {
		return deptName;
	}
	std::string getDeptManagerId() const {
		if (Validation::validateID(std::to_string(deptManagerId)))
			return std::to_string(id);
		return "";
	}
	std::string getDescription() const {
		return description;
	}
	std::string getTableName() const {
		return "Department";
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

	bool setDeptName(std::string str) {
		if (Validation::validateString(str)) {
			deptName = str;
			return true;
		}
		return false;
	}

	bool setDeptManagerId(std::string str) {
		if (Validation::validateID(str)) {
			try {
				deptManagerId = stoi(str);
				return true;
			}
			catch (...) {
				return false;
			}
		}
		return false;

	}

	bool setDescription(std::string str) {
		if (Validation::validateString(str)) {
			description = str;
			return true;
		}
		return false;
	}
	std::map<int, getsetmap<Department>>& getMap() const {
		return gettersetter;
	}

	
private:
	DID id;
	std::string deptName;
	EID deptManagerId;
	std::string description;
	inline static std::map<int, getsetmap<Department>> gettersetter = {
		{1, getsetmap<Department>{"ID",& setid,& getid, false }},
		{2, getsetmap<Department>{"DeptName",& setDeptName,& getDeptName, false}},
		{3, getsetmap<Department>{"DeptManager",& setDeptManagerId,& getDeptManagerId, true}},
		{4, getsetmap<Department>{"Description",& setDescription,& getDescription, true}},
	};
};
#endif