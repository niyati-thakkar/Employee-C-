#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_
#include<iostream>
#include<string>
#include<map>
#include<optional>
template<typename T>
struct getsetmap {
	std::string name;
	bool(T::* setter)(std::string);
	std::optional<std::string>(T::* getter)() const;
	bool isOptional;
};

class Validation {
public:
	static bool validateID(std::string id) {
		try {
			stoi(id);
			return true;
		}
		catch (...) {
			return false;
		}
	}
	static bool validateString(std::string str) {
		if (str == "#" || str.length() == 0) {
			return false;
		}
		return true;
	}
};

class Employee {
	



	int id;
	std::optional<std::string> name;


public:
	inline static std::string TABLE_NAME = "emp";
	std::optional<std::string> getid() const{
		return std::to_string(id);
	}
	std::optional<std::string> getname() const {
		return name;
	}

	bool setid(std::string i) {
		if (Validation::validateID(i)) {
			id = stoi(i);
			return true;
		}
		return false;
			
	};

	bool setname(std::string n) {
		if (Validation::validateString(n)) {
			name = n;
			return true;
		}
		else {
			return false;
		}
		
	}
	inline static std::map<int, getsetmap<Employee>> gettersetter = {
		{1, getsetmap<Employee>{"id",&setid, &getid, false }},
		{2, getsetmap<Employee>{"name",&setname, &getname, true}}
	};


};

#endif