#include "AutomatonException.h"


AutomatonException::AutomatonException(const char* msg, const char* stateTry, const char* stateMarked, const char* file, int line, const char* func) :std::exception(msg) {
	this->stateTry = new char[strlen(stateTry) + 1];
	strcpy_s(this->stateTry, strlen(stateTry) + 1, stateTry);

	this->stateMarked = new char[strlen(stateMarked) + 1];
	strcpy_s(this->stateMarked, strlen(stateMarked) + 1, stateMarked);

	this->file = new char[strlen(file) + 1];
	strcpy_s(this->file, strlen(file) + 1, file);

	this->line = line;

	this->func = new char[strlen(func) + 1]; 
	strcpy_s(this->func, strlen(func) + 1, func);
}

AutomatonException::~AutomatonException() {
	if (stateTry != nullptr) {
		delete[] stateTry;
	}
	if (stateMarked != nullptr) {
		delete[] stateMarked;
	}
	if (file != nullptr) {
		delete[] file;
	}
	if (func != nullptr) {
		delete[] func;
	}
}

const char* AutomatonException::getFile() const{
	return file;
}
int AutomatonException::getLine() const{
	return line;
}
const char* AutomatonException::getFunc() const{
	return func;
}

const char* AutomatonException::getStateTry() const {
	return stateTry;
}
const char* AutomatonException::getStateMarked() const {
	return stateMarked;
}


int AutomatonException::print() const {
	std::cout << "Wanted entry state: " << stateTry << std::endl;
	std::cout << "Current entry state: " << stateMarked << std::endl;
	std::cout << "In file: " << file << std::endl;
	std::cout << "Function: " << func << std::endl;
	std::cout << "Line: " << line << std::endl;
	return 0;
}

std::ostream& operator<<(std::ostream& out, AutomatonException& rhs) {
	out << rhs.what() << std::endl;
	out << "Wanted entry state: " << rhs.getStateTry() << std::endl;
	out << "Current entry state: " << rhs.getStateMarked() << std::endl;
	out << "In file: " << rhs.getFile() << std::endl;
	out << "Function: " << rhs.getFunc() << std::endl;
	out << "Line: " << rhs.getLine() << std::endl;
	return out;
}