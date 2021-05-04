#include "State.h"


State::State(const char* name):stateName(new char [strlen(name)+1]) {
	strcpy_s(stateName, strlen(name) + 1, name);
}

State::State(const State& rhs): stateName ( new char[strlen(rhs.stateName) + 1]) {
	strcpy_s(stateName, strlen(rhs.stateName) + 1,rhs.stateName); // destination, number of el, sorce
}

State& State::operator=(const State& rhs) {
	if (this != &rhs) {
		if (stateName != nullptr) {
			delete[] stateName;
		}
		stateName = new char[strlen(rhs.stateName) + 1];
		strcpy_s(stateName, strlen(rhs.stateName) + 1, rhs.stateName);
	}
	return *this;
}

int State::setStateName(char* name) {
	stateName = new char[strlen(name) + 1];
	strcpy_s(stateName, strlen(name) + 1, name);
	return 0;
}
char* State::getStateName()const {
	return stateName;
}

State::~State() { 
	if (stateName != nullptr) {
		delete[] stateName;
	}
}

std::ostream& operator<<(std::ostream& out,const State& rhs) {
	out << rhs.getStateName();
	return out;
}

std::istream& operator>>(std::istream& in, State& rhs) {
	char* name;
	in >> name;
	rhs.setStateName(name);
	if (name != nullptr) {
		delete[] name;
	};
	return in;
}

