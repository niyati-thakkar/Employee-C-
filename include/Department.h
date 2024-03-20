#ifndef _DEPARTMENT_H_
#define _DEPARTMENT_H_
#include<string>
#include "Utility.h"
#include<map>


class Department {
public:

	/**********************************************************************************		getters	*************************************************************************************/

	std::string getid() const{
		if (id != 0)
			return std::to_string(id);
		return "";
	}

	std::string getDeptName() const {
		return deptName;
	}
	std::string getDeptManagerId() const {
		if (deptManagerId != 0)
			return std::to_string(deptManagerId);
		return "";
	}
	std::string getDescription() const {
		return description;
	}
	static std::map<int, getsetmap<Department>>& getMap() {
		return gettersetter;
	}
	static size_t getLastKey() {
		return gettersetter.size();
	}
	static std::string getTableName() {
		return TABLE_NAME;
	}

	/**********************************************************************************		setters	*************************************************************************************/


	bool setid(std::string str) {
		if (Validation::validateID(str) && str[0] == '2') {
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
		if (Validation::validateID(str) && str[0] == '1') {
			try {
				if (CRUD::isKeyPresent("Employee", "EmpId", str)) {
					deptManagerId = stoi(str);
					return true;
				}
				
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
	

	
private:
	DID id{};
	std::string deptName;
	MID deptManagerId{};
	std::string description;
	inline static std::string TABLE_NAME = "DEPARTMENT";
	inline static std::map<int, getsetmap<Department>> gettersetter = {
		{1, getsetmap<Department>{"ID",& setid,& getid, false }},
		{2, getsetmap<Department>{"DeptName",& setDeptName,& getDeptName, false}},
		{3, getsetmap<Department>{"DeptManager",& setDeptManagerId,& getDeptManagerId, false}},
		{4, getsetmap<Department>{"Description",& setDescription,& getDescription, true}},
	};
};
#endif