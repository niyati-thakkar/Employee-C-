#ifndef _TECH_H_
#define _TECH_H_
#include<string>

#include "Utility.h"

#include "Employee.h"

#include<map>


class Tech : public Employee {
public: 
	/**********************************************************************************		getters		*************************************************************************************/

		std::string getid() const {
			if (id != 0)
				return std::to_string(id);
			return "";
		}

	  std::string getTechSpecialization() const {
		  return techSpecialization;
	  }

	  std::string getCurrentProject() const {
		  return currentProject;
	  }
	  
	  std::string getEmpId() const {
		  if (empId != 0)
			  return std::to_string(empId);
		  return "";
	  }
	  static std::map <int, getsetmap < Tech >>& getMap() {
		  return gettersetter;
	  }

	  static size_t getLastKey() {
		  return gettersetter.size() - 1;
	  }
	  static std::string getTableName() {
		  return TABLE_NAME;
	  }

	  /**********************************************************************************		setters		*************************************************************************************/

	  bool setid(std::string str) {
		  if (Validation::validateID(str) && str[0] == '4') {
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
	  bool setCurrentProject(std::string str) {
		  if (Validation::validateString(str)) {
			  currentProject = str;
			  return true;
		  }
		  return false;
	  }
	  
private: TID id{};
	   EID empId{};
	   std::string techSpecialization;
	   std::string currentProject;
	   inline static std::string TABLE_NAME = "TECH";
	   inline static std::map < int,
		   getsetmap < Tech >> gettersetter = {
			   {
				   0,
				   getsetmap < Tech > {
					   "EmpId",
					   & setEmpId,
					   & getEmpId,
					   false
				   }
			   },
			   {
				   1,
				   getsetmap < Tech > {
					   "ID",
					   & setid,
					   & getid,
					   false
				   }
			   },
			   {
				   2,
				   getsetmap < Tech > {
					   "TechSpecialization",
					   & setTechSpecialization,
					   & getTechSpecialization,
					   false
				   }
			   },
			   {
				   3,
				   getsetmap < Tech > {
					   "CurrentProject",
					   & setCurrentProject,
					   & getCurrentProject,
					   true
				   }
			   }
	   };
};
#endif