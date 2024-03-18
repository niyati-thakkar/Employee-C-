#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_
#include<iostream>
#include<string>
#include<map>
#include<optional>
#include "utility.h"
#include "crud.h"

class Address {
public:
	std::string getid() const {
		return std::to_string(id);
	}

	std::string getLocation() const {
		return location;
	}
	std::string getCity() const {
		return city;
	}
	std::string getState() const {
		return state;
	}
	std::string getPincode() const {
		return std::to_string(pincode);
	}
	std::string getEmpId() const {
		if (empId != 0)
			return std::to_string(empId);
		return "";
	}
	static size_t getLastKey() {
		return gettersetter.size() - 1;
	}
	bool setid(std::string str) {
		if (Validation::validateID(str) && str[0] == '1' && str[1] == '1') {
			try {
				id = stoi(str);
				return true;
			}
			catch (...) {
				return false;
			}
			
			return true;
		}
		return false;
	}
	bool setLocation(std::string loc) {
		if (Validation::validateString(loc)) {
			location = loc;
			return true;
		}
		return false;
	}
	bool setState(std::string st) {
		if (Validation::validateString(st)) {
			state = st;
			return true;
		}
		return false;
	}
	bool setCity(std::string ct) {
		if (Validation::validateString(ct)) {
			city = ct;
			return true;
		}
		return false;
	}
	bool setEmpId(std::string str) {
		if (Validation::validateID(str)) {
			try {
				empId = stoi(str);
				if (CRUD::isKeyPresent("Employee","EmpId", str)) {
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
	bool setPincode(std::string pin) {
		if (Validation::validatePincode(pin)) {
			try {
				int temp = stoi(pin);
				if (temp > 99999) {
					pincode = temp;
					return true;
				}
			}
			catch (...) {
				return false;
			}
			return false;
		}
		return false;
	}
	static std::string getTableName() {
		return "Address";
}
	static std::map<int, getsetmap<Address>>& getMap() {
		return gettersetter;
	}
private:
	AID id;
	EID empId;
	std::string location;
	std::string city;
	std::string state;
	PIN pincode;
	inline static std::map<int, getsetmap<Address>> gettersetter = {
		{0, getsetmap<Address>{"EmpId",& setEmpId,& getEmpId, false }},
		{1, getsetmap<Address>{"ID",& setid,&getid, false }},
		{2, getsetmap<Address>{"Location",&setLocation,&getLocation, false}},
		{3, getsetmap<Address>{"City",& setCity,& getCity, false}},
		{4, getsetmap<Address>{"State",& setState,& getState, false}},
		{5, getsetmap<Address>{"Pincode",& setPincode,& getPincode, false}}
	};
};


class Employee {
	
public:
	std::string getid() const{
		if(Validation::validateID(std::to_string(id)))
			return std::to_string(id);
		return "";
	}

	std::string getFname() const {
		return fname;
	}
	std::string getMname() const {
		return mname;
	}
	std::string getLname() const {
		return lname;
	}

	std::string getContact() const {
		return contact;
	}

	std::string getEmail() const {
		return email;
	}

	Address& getAddress() {
		return empAddr;
	}

	std::string getDeptId() const {
		if (Validation::validateID(std::to_string(deptId)))
			return std::to_string(deptId);
		return "";
	}

	std::string getReportingManagerId() const {
		if (Validation::validateID(std::to_string(reportingManagerId)))
			return std::to_string(reportingManagerId);
		return "";
	}

	static std::string getTableName() {
		return TABLE_NAME;
	}

	std::string getDOB() const {
		return DOB;
	}

	bool setid(std::string i) {
		if (Validation::validateID(i)) {
			try {
				id = stoi(i);
				return true;
			}
			catch (...) {
				return false;
			}
			
		}
		return false;
			
	};

	bool setFname(std::string str) {
		if (Validation::validateString(str)) {
			fname = str;
			return true;
		}
		return false;
	}
	bool setMname(std::string str) {
		if (str[0] == '#') {
			mname = "";
			return true;
		}
		if (Validation::validateString(str)) {
			mname = str;
			return true;
		}
		return false;
	}
	bool setLname(std::string str) {
		if (Validation::validateString(str)) {
			lname = str;
			return true;
		}
		return false;
	}

	bool setAddress(std::string) {
		return true;
	}

	bool setContact(std::string str) {
		if (Validation::validateContact(str)) {
			contact = str;
			return true;
		}
		return false;
	}

	bool setEmail(std::string str) {
		if (str[0] == '#') {
			email = "";
			return true;
		}
		if(Validation::validateEmail(str)) {
			contact = str;
			return true;
		}
		return false;
		return false;
	}

	bool setDOB(std::string str) {
		if (Validation::validateDate(str)) {
			DOB = str;
			return true;
		}
		return false;
	}
	bool setDeptId(std::string str) {
		if (Validation::validateID(str)) {
			try {
				deptId = stoi(str);
				if (CRUD::isKeyPresent("Department","ID", str)) {
					return true;
				}
				else {
					std::cout << "Department with given ID doesn't exists!" << "\n";
				}
			}
			catch (...) {
				return false;
			}
		}
		return false;
	}

	bool setReportingManagerId(std::string str) {
		if (Validation::validateID(str)) {
			try {
				reportingManagerId = stoi(str);
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

	std::map<int, getsetmap<Employee>>& getMap() const {
		return gettersetter;
	}

	static size_t getLastKey() {
		return gettersetter.size();
	}
	
private:
	EID id{};
	std::string fname;
	std::string mname;
	std::string lname;
	std::string contact;
	std::string email;
	std::string DOB;
	Address empAddr;
	DID deptId{};
	EID reportingManagerId{};
	static inline std::string TABLE_NAME = "Employee";
	inline static std::map<int, getsetmap<Employee>> gettersetter = {
		{1, getsetmap<Employee>{"EmpId",& setid,& getid, false }},
		{2, getsetmap<Employee>{"FirstName",& setFname,& getFname, false}},
		{3, getsetmap<Employee>{"MiddleName",& setMname,& getMname, true}},
		{4, getsetmap<Employee>{"LastName",& setLname,& getLname, false}},
		{5, getsetmap<Employee>{"Contact",& setContact,& getContact, false}},
		{6, getsetmap<Employee>{"Email",& setEmail,& getEmail, true}},
		{7, getsetmap<Employee>{"DOB",&setDOB, &getDOB, false}},
		{8, getsetmap<Employee>{"DepartmentID",& setDeptId,& getDeptId, false}},
		{9, getsetmap<Employee>{"ReportingManagerID",& setReportingManagerId,& getReportingManagerId, true}},
	};
};


#endif