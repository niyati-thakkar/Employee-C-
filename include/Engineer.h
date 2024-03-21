#ifndef _Engineer_H_
#define _Engineer_H_
#include<string>

#include "Utility.h"

#include "Employee.h"

#include<map>


class Engineer : public Employee {
public: 
	/**********************************************************************************		getters		*************************************************************************************/

		std::string getid() const {
			if (id != 0)
				return std::to_string(id);
			return "";
		}

	  std::string getEngineerSpecialization() const {
		  return EngineerSpecialization;
	  }

	  std::string getCurrentProject() const {
		  return currentProject;
	  }
	  
	  std::string getEmpId() const {
		  if (empId != 0)
			  return std::to_string(empId);
		  return "";
	  }
	  static std::map <int, getsetmap < Engineer >>& getMap() {
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

	  bool setEngineerSpecialization(std::string str) {
		  if (Validation::validateString(str)) {
			  EngineerSpecialization = str;
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
	   std::string EngineerSpecialization;
	   std::string currentProject;
	   inline static std::string TABLE_NAME = "Engineer";
	   inline static std::map < int,
		   getsetmap < Engineer >> gettersetter = {
			   {
				   0,
				   getsetmap < Engineer > {
					   "EmpId",
					   & setEmpId,
					   & getEmpId,
					   false
				   }
			   },
			   {
				   1,
				   getsetmap < Engineer > {
					   "ID",
					   & setid,
					   & getid,
					   false
				   }
			   },
			   {
				   2,
				   getsetmap < Engineer > {
					   "EngineerSpecialization",
					   & setEngineerSpecialization,
					   & getEngineerSpecialization,
					   false
				   }
			   },
			   {
				   3,
				   getsetmap < Engineer > {
					   "CurrentProject",
					   & setCurrentProject,
					   & getCurrentProject,
					   true
				   }
			   }
	   };
};
#endif