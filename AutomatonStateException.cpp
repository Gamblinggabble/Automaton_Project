#include "AutomatonStateException.h"

AutomatonStateException::AutomatonStateException(const State& stateNotFound, const char* file, const char* fn, unsigned line) 
	:file (new char [strlen(file)+1]),fn (new char [strlen(fn)+1]), stateNotFound (stateNotFound), line (line) {
	
	this->file = new char[strlen(file) + 1];
	strcpy_s(this->file, strlen(file) + 1, file);

	this->fn = new char[strlen(fn) + 1];
	strcpy_s(this->fn, strlen(fn) + 1, fn);
}

AutomatonStateException::AutomatonStateException(AutomatonStateException& rhs) : std::exception(rhs) {
	if (rhs.file != nullptr) {
		if (file != nullptr) {
			delete[] file;
		}
		file = new char[strlen(rhs.file) + 1];
		strcpy_s(file, strlen(rhs.file) + 1, rhs.file);
	}
	else fn = nullptr;

	if (rhs.fn != nullptr) {
		if (fn != nullptr) {
			delete[] fn;
		}
		fn = new char[strlen(rhs.fn) + 1];
		strcpy_s(fn, strlen(rhs.fn) + 1, rhs.fn);
	}
	else fn = nullptr;

}

AutomatonStateException& AutomatonStateException::operator=(const AutomatonStateException& rhs) {
	if (this != &rhs) {
		if (rhs.file != nullptr) {
			if (file != nullptr) {
				delete[] file;
			}
			file = new char[strlen(rhs.file) + 1];
			strcpy_s(file, strlen(rhs.file) + 1, rhs.file);
		}
		else fn = nullptr;
		if (rhs.fn != nullptr) {
			if (fn != nullptr) {
				delete[] fn;
			}
			fn = new char[strlen(rhs.fn) + 1];
			strcpy_s(fn, strlen(rhs.fn) + 1, rhs.fn);
		}
		else fn = nullptr;
	}

	return *this;
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

//Dari TODO: add setters

std::ostream& operator <<(std::ostream& out, const AutomatonStateException& rhs) {
	out << rhs.what() << std::endl;
	out << "In file: " << rhs.getFile() << std::endl;
	out << "Function used: " << rhs.getFn() << std::endl;
	out << "Wanted state Not Found: " << rhs.getStateNotFound() << std::endl;
	out << "Line: " << rhs.getLine() << std::endl;
	return out;
}