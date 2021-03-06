#include "State.h"
#include "AutomatonException.h"
#include <iostream>
#include <string>
#include <sstream>

State::State(const char* name) : stateName(new char[strlen(name) + 1]) {
	strcpy_s(stateName, strlen(name) + 1, name);
}

State::State(const State& rhs) : stateName(new char[strlen(rhs.stateName) + 1]) {
	strcpy_s(stateName, strlen(rhs.stateName) + 1, rhs.stateName); // destination, number of el, source
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

bool State::operator==(const State& rhs) {
	if (strcmp(stateName, rhs.getStateName()) == 0)
		return true;

	return false;
}

int State::setStateName(char* name) {
	if (stateName != nullptr) {
		delete[] stateName;
	}
	stateName = new char[strlen(name) + 1];
	strcpy_s(stateName, strlen(name) + 1, name);
	return 0;
}
char* State::getStateName() const {
	return stateName;
}

State::~State() {
	if (stateName != nullptr) {
		delete[] stateName;
	}
}

std::ostream& operator<<(std::ostream& out, const State& rhs) {
	out << rhs.getStateName();
	return out;
}

std::istream& operator>>(std::istream& lhs, State& rhs)
{
	char arr[50];
	lhs >> arr;
	rhs.setStateName(arr);
	return lhs;
}

