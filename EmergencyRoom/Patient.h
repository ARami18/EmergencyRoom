#pragma once
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <string>
#include <sstream>
#include <iomanip>

class Patient
{
private:
	std::string name_;
	std::string ailment_;
	unsigned int severity_;
	unsigned int time_criticality_;
	unsigned int contagiousness_;

public:
	Patient(std::string name, std::string ailment,
		unsigned int severity,
		unsigned int time_criticality,
		unsigned int contagiousness) :
		name_(name), ailment_(ailment), severity_(severity),
		time_criticality_(time_criticality), contagiousness_(contagiousness) {};

	~Patient() {}

	unsigned int get_priority() const;

	std::string to_string() const;
	
	inline std::string getName() { return name_;  }
	inline std::string getAilment() { return ailment_; }
	constexpr unsigned int getSev() { return severity_;  }
	constexpr unsigned int getTimeCrit() { return time_criticality_; }
	constexpr unsigned int getCont() { return contagiousness_; }
};

std::ostream& operator <<(std::ostream& os, Patient const& patient);
bool operator <(Patient const& lhs, Patient const& rhs);