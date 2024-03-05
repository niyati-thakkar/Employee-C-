#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_
#include<iostream>
#include<string>
#include<map>
template<typename T>
struct getsetmap {
	std::string name;
	bool(T::* setter)(std::string);
	std::string(T::* getter)() const;
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
};

class Employee {
	int id;
	std::string name;
public:
	
	std::string getid() const{
		return std::to_string(id);
	}
	std::string getname() const {
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
		name = n;
		return true;
	}
	inline static std::map<int, getsetmap<Employee>> gettersetter = {
		{1, getsetmap<Employee>{"id", &setid, &getid}},
		{2, getsetmap<Employee>{"name",&setname, &getname}}
	};


};

#endif