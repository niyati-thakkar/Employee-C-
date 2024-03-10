#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_
#include<iostream>
#include<string>
#include<map>
#include<optional>
#include "utility.h"

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

	bool setid(std::string str) {
		if (Validation::validateID(str) && str[0] == '1' && str[1] == '1') {
			try {
				id = stoi(str);
				return true;
			}
			catch (...) {
				return false;
			}
			return false;
			
		}
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
private:
	AID id;
	std::string location;
	std::string city;
	std::string state;
	PIN pincode;
	inline static std::map<int, getsetmap<Address>> gettersetter = {
		{1, getsetmap<Address>{"ID",& setid,&getid, false }},
		{2, getsetmap<Address>{"Location",&setLocation,&getLocation, false}},
		{3, getsetmap<Address>{"City",& setCity,& getCity, true}},
		{4, getsetmap<Address>{"State",& setState,& getState, false}},
		{5, getsetmap<Address>{"Pincode",& setPincode,& getPincode, false}},
	};
};


class Employee {
	
public:
	std::string getid() const{
		return std::to_string(id);
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

	std::string getAddress() const {
		return "address";
	}

	std::string getDeptId() const {
		return std::to_string(deptId);
	}

	std::string getReportingManagerId() const {
		return std::to_string(reportingManagerId);
	}

	std::string getTableName() {
		return TABLE_NAME;
	}

	bool setid(std::string i) {
		if (Validation::validateID(i)) {
			id = stoi(i);
			return true;
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
		if(Validation::validateContact(str)) {
			contact = str;
			return true;
		}
		return false;
	}

	bool setDeptId(std::string str) {
		if (Validation::validateID(str)) {
			try {
				deptId = stoi(str);
				return true;
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
				return true;
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
	
private:
	EID id;
	std::string fname;
	std::string mname;
	std::string lname;
	std::string contact;
	std::string email;
	Address empAddr;
	DID deptId;
	EID reportingManagerId;
	static inline std::string TABLE_NAME = "Employee";
	inline static std::map<int, getsetmap<Employee>> gettersetter = {
		{1, getsetmap<Employee>{"ID",& setid,& getid, false }},
		{2, getsetmap<Employee>{"FirstName",& setFname,& getFname, false}},
		{3, getsetmap<Employee>{"MiddleName",& setMname,& getMname, true}},
		{4, getsetmap<Employee>{"LastName",& setLname,& getLname, false}},
		{5, getsetmap<Employee>{"Contact",& setContact,& getContact, false}},
		{6, getsetmap<Employee>{"Email",& setEmail,& getEmail, true}},
		{7, getsetmap<Employee>{"DepartmentID",& setDeptId,& getDeptId, false}},
		{8, getsetmap<Employee>{"ReportingManagerID",& setReportingManagerId,& getReportingManagerId, false}},
	};
};


#endif