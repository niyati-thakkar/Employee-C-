#define PIN int
#define EID int
#define DID int
#define MID int
#define EnID int
#define AID int
#define HRID int
#include<string>
#include<regex>
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
		return id.length() == 6;
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
		return std::regex_match(str, std::regex("^[\w-\.]+@([\w-]+\.)+[\w-]{2,4}$"));
	}
};