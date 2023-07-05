#include "Patient.h"

unsigned int Patient::get_priority() const {
	return severity_ + time_criticality_ + contagiousness_;
}

std::string Patient::to_string() const {
	std::stringstream ss;
	ss << std::setw(20) << name_ <<
		std::setw(20) << ailment_ <<
		std::setw(11) << severity_ <<
		std::setw(19) << time_criticality_ <<
		std::setw(17) << contagiousness_ <<
		std::setw(11) << get_priority() << std::endl;
	return ss.str();
}

std::ostream& operator <<(std::ostream& os, Patient const& patient) {
	return os << patient.to_string();
}

bool operator <(Patient const& lhs, Patient const& rhs) {
	return lhs.get_priority() < rhs.get_priority();
}