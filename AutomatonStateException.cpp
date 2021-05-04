#include "AutomatonStateException.h"

AutomatonStateException::AutomatonStateException(const State& stateNotFound, const char* file = "No data", const char* fn = "No data", unsigned line = 0) {
	//:State& (stateNotFound),file (new char [strlen(file)+1]),fn (new char [strlen(fn)+1]), line (line) {
	//strcpy_s(file, strlen(file) + 1, file);

	this->stateNotFound;
	
	this->file = new char[strlen(file) + 1];
	strcpy_s(this->file, strlen(file) + 1, file);

	this->fn = new char[strlen(fn) + 1];
	strcpy_s(this->fn, strlen(fn) + 1, fn);

	this->line = line;

}

AutomatonStateException::~AutomatonStateException() {

	if (file != nullptr) {
		delete[] file;
	};

	if (fn !=nullptr) {
		delete[] fn;
	};

	if (stateNotFound != nullptr) {
		delete[]stateNotFound;
	};

}

const char* AutomatonStateException::getFile() const {
	return file;
}

const char* AutomatonStateException::getFn() const {
	return fn;
}

unsigned AutomatonStateException::getLine() const {
	return line;
}

int AutomatonStateException::print() const {

	std::cout << "In File: " << file << std::endl;
	std::cout << "Function used: " << fn << std::endl;
	std::cout << "Wanted state Not Found: " << stateNotFound << std::endl;
	std::cout << "Line: " << line << std::endl;

}

std::ostream& operator <<(std::ostream& out, AutomatonStateException& rhs) {
	out << rhs.what() << std::endl;
	out << "In file: " << rhs.getFile() << std::endl;
	out << "Function used: " << rhs.getFn() << std::endl;
	out << "Wanted state Not Found: " << rhs.getstateNotFound() << std::endl;
	out << "Line: " << rhs.getLine() << std::endl;
	return out;

}