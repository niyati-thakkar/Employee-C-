#ifndef _UTILITY_H
#define _UTILITY_H
#define PIN int
#define EID int
#define DID int
#define MID int
#define TID int
#define AID int
#define HID int
#include<string>

#include<regex>

#include <type_traits>

#include<iostream>

template < typename T >
struct getsetmap {
	std::string name;
	bool(T::* setter)(std::string);
	std::string(T::* getter)() const;
	bool isOptional;
};

namespace Validation {
	bool validateID(std::string id) {
		return id.length() == 7;
	}
	bool validateString(std::string str) {
		if (str.length() != 0 && std::regex_match(str, std::regex("^[a-zA-Z][-a-zA-Z ']{1,49}$"))) {
			return true;
		}
		return false;
	}
	bool validatePincode(std::string str) {
		return str.length() == 6;
	}
	bool validateContact(std::string str) {
		return std::regex_match(str, std::regex("\\(?\\d{3}[-\\) ]+\\d{3}[- ]?\\d{4}"));
	}
	bool validateEmail(std::string str) {
		return std::regex_match(str, std::regex(R"([_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,4}))"));
	}
	bool validateDate(std::string str) {
		return std::regex_match(str, std::regex(R"(^(?:(?:31(\/|-|\.)(?:0?[13578]|1[02]))\1|(?:(?:29|30)(\/|-|\.)(?:0?[13-9]|1[0-2])\2))(?:(?:1[6-9]|[2-9]\d)?\d{2})$|^(?:29(\/|-|\.)0?2\3(?:(?:(?:1[6-9]|[2-9]\d)?(?:0[48]|[2468][048]|[13579][26])|(?:(?:16|[2468][048]|[3579][26])00))))$|^(?:0?[1-9]|1\d|2[0-8])(\/|-|\.)(?:(?:0?[1-9])|(?:1[0-2]))\4(?:(?:1[6-9]|[2-9]\d)?\d{2})$)"));
	}

};

namespace Utility {

	std::string backMessage = "0. Go back to previous menu!";
	std::string exitMessage = "100. To exit!";

	template <class T, class U>
	struct are_same_template : std::is_same<T, U>
	{};

	template <template<class...> class T, class T1, class T2>
	struct are_same_template<T<T1>, T<T2>> : std::true_type
	{};
	template<typename T1>
	[[nodiscard]] bool setInput(T1& res) {
		std::string arg;
		std::getline(std::cin, arg);
		if constexpr (std::is_same_v<T1, std::string>) {
			res = arg;
		}
		else if constexpr (std::is_arithmetic_v <T1>) {
			try {
				res = stoi(arg);
			}
			catch (...) {
				return false;
			}
		}
		else {
			res = arg[0];
		}
		return true;
	}

	bool tryAgain() {
		std::cout << "The entered value is not valid. Do you wish to try again?\n1. YES\n2. NO, Go Back to previous Menu!\n";
		int opt;
		if (setInput(opt))
			return opt == 1;
		return false;
	}
	
	template < typename T1, typename T2>
	[[nodiscard]] bool getUserInput(T1& e, getsetmap < T2 >& map) {
		do {
			std::cout << "Enter " << map.name << "\n";
			std::string temp;
			if (setInput(temp)) {
				if ((e.*map.setter)(temp)) {
					return true;
				}
			}
		} while (tryAgain());
		return false;
	}
	template < typename...Args >
	[[nodiscard]] int takeOption(Args...args) {
		std::cout << Utility::backMessage << "\n";
		int i = 1;
		((std::cout << i++ << ". " << std::forward < Args >(args) << " \n"), ...);
		std::cout << Utility::exitMessage << "\n";
		int option = 0;
		if (setInput(option)) {
			if (option == 100) {
				exit(0);
			}
			if (option < 0 || option >= i) {
				std::cout << "Please enter a valid option" << "\n";
				if (setInput(option) && (option < 0 || option >= i)) {
					std::cout << "Invalid Option Selected!" << "\n";
					return 0;
				}
			}
		}
		
		return option;
	}
};
#endif