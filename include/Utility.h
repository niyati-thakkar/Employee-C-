#ifndef _UTILITY_H
#define _UTILITY_H
#define PIN int
#define EID int
#define DID int
#define MID int
#define EnID int
#define AID int
#define HRID int
#include<string>
#include<regex>
#include<iostream>
template<typename T>
struct getsetmap {
	std::string name;
	bool(T::* setter)(std::string);
	std::string(T::* getter)() const;
	bool isOptional;
};

class Validation {
public:
	static bool validateID(std::string id) {
		//return id.length() == 6;
		return true;
	}
	static bool validateString(std::string str) {
		if (str.length() == 0) {
			return false;
		}
		return true;
	}
	static bool validatePincode(std::string str) {
		return str.length() == 6;
	}
	static bool validateContact(std::string str) {
		return std::regex_match(str, std::regex("\\(?\\d{3}[-\\) ]+\\d{3}[- ]?\\d{4}"));
	}
	static bool validateEmail(std::string str) {
		return std::regex_match(str, std::regex(R"([_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,4}))"));
	}
};

class Utility {
public:

	static inline std::string backMessage = "0. Go back to previous menu!";
	static inline std::string exitMessage = "100. To exit!";

	static bool tryAgain() {
		std::cout << "The entered value is not valid. Do you wish to try again?\n1. YES\n2. NO, Go Back to previous Menu!";
		int opt;
		std::cin >> opt;
		return opt == 1 ? true : false;
	}
	template<typename T>
	[[nodiscard]] static bool getUserInput(T& e, int id) {
		auto map = e.getMap()[id];
		std::cout << "Enter " << map.name << "\n";
		std::string temp;
		std::cin >> temp;
		if (!(e.*map.setter)(temp)) {
			std::cout << "Invalid " << map.name << " (Try Again)" << "\n";
			std::cin >> temp;
			if (!(e.*map.setter)(temp)) {
				return false;
			}

		}
		return true;
	}
	template<typename ...Args>
	[[nodiscard]] static int takeOption(Args ...args) {
		std::cout << Utility::backMessage << "\n";
		int i = 1;
		((std::cout << i++ << ". " << std::forward<Args>(args) << " \n"), ...);
		std::cout << Utility::exitMessage << "\n";
		int option;
		std::cin >> option;
		if (option == 100) {
			exit(0);
		}
		if (option < 0 || option >= i) {
			std::cout << "Please enter a valid option" << "\n";
			std::cin >> option;
		}
		if (option < 0 || option >= i) {
			std::cout << "Invalid Option Selected!" << "\n";
			return 0;
		}
		return option;

	}
};
#endif