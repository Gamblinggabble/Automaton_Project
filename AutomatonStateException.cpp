#include "AutomatonStateException.h"

AutomatonStateException::AutomatonStateException(const State& stateNotFound, const char* file, const char* fn, unsigned line) 
	:file (new char [strlen(file)+1]),fn (new char [strlen(fn)+1]), stateNotFound (stateNotFound), line (line) {
	
	this->file = new char[strlen(file) + 1];
	strcpy_s(this->file, strlen(file) + 1, file);

	this->fn = new char[strlen(fn) + 1];
	strcpy_s(this->fn, strlen(fn) + 1, fn);
}

AutomatonStateException::~AutomatonStateException() {

	if (file != nullptr) {
		delete[] file;
	};

	if (fn !=nullptr) {
		delete[] fn;
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

const State& AutomatonStateException::getStateNotFound() const {
	return stateNotFound;
};


std::ostream& operator <<(std::ostream& out, const AutomatonStateException& rhs) {
	out << rhs.what() << std::endl;
	out << "In file: " << rhs.getFile() << std::endl;
	out << "Function used: " << rhs.getFn() << std::endl;
	out << "Wanted state Not Found: " << rhs.getStateNotFound() << std::endl;
	out << "Line: " << rhs.getLine() << std::endl;
	return out;
}