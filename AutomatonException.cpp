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

AutomatonException::AutomatonException(AutomatonException& rhs): std::exception(rhs) {
		if (rhs.file != nullptr) {
			if (file != nullptr) {
				delete[] file;
			}
			file = new char[strlen(rhs.file) + 1];
			strcpy_s(file, strlen(rhs.file) + 1, rhs.file);
		}
		else file = nullptr;

		line = rhs.line;

		if (rhs.func != nullptr) {
			if (func != nullptr) {
				delete[] func;
			}
			func = new char[strlen(rhs.func) + 1];
			strcpy_s(func, strlen(rhs.func) + 1, rhs.func);
		}
		else func = nullptr;

		if (rhs.stateTry != nullptr) {
			if (stateTry != nullptr) {
				delete[] stateTry;
			}
			stateTry = new char[strlen(rhs.stateTry) + 1];
			strcpy_s(stateTry, strlen(rhs.stateTry) + 1, rhs.stateTry);
		}
		else stateTry = nullptr;

		if (rhs.stateMarked != nullptr) {
			if (stateMarked != nullptr) {
				delete [] stateMarked;
			}
			stateMarked = new char[strlen(rhs.stateMarked) + 1];
			strcpy_s(stateMarked, strlen(rhs.stateMarked) + 1, rhs.stateMarked);
		}
		else stateMarked = nullptr;
}

AutomatonException& AutomatonException::operator=(const AutomatonException& rhs) {
	if (this != &rhs) {
		if (rhs.file != nullptr) {
			if (file != nullptr) {
				delete[] file;
			}
			file = new char[strlen(rhs.file) + 1];
			strcpy_s(file, strlen(rhs.file) + 1, rhs.file);
		}
		else file = nullptr;

		line = rhs.line;

		if (rhs.func != nullptr) {
			if (func != nullptr) {
				delete[] func;
			}
			func = new char[strlen(rhs.func) + 1];
			strcpy_s(func, strlen(rhs.func) + 1, rhs.func);
		}
		else func = nullptr;

		if (rhs.stateTry != nullptr) {
			if (stateTry != nullptr) {
				delete[] stateTry;
			}
			stateTry = new char[strlen(rhs.stateTry) + 1];
			strcpy_s(stateTry, strlen(rhs.stateTry) + 1, rhs.stateTry);
		}
		else stateTry = nullptr;

		if (rhs.stateMarked != nullptr) {
			if (stateMarked != nullptr) {
				delete[] stateMarked;
			}
			stateMarked = new char[strlen(rhs.stateMarked) + 1];
			strcpy_s(stateMarked, strlen(rhs.stateMarked) + 1, rhs.stateMarked);
		}
		else stateMarked = nullptr;

	}
	return *this;
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

int AutomatonException::setFile(char* file) {
	if (this->file != nullptr) {
		delete[] this->file;
	}
	this->file = new char[strlen(file) + 1];
	//Трябва ли да има +1 в копирането
	strcpy_s(this->file, strlen(file) + 1, file);
	return 0;
}
int AutomatonException::setLine(int line) {
	this->line = line;
	return 0;
}
int AutomatonException::setFucn(char* func) {
	if (this->func != nullptr) {
		delete[] this->func;
	}
	this->func = new char[strlen(func) + 1];
	strcpy_s(this->func, strlen(func) + 1, func);
	return 0;
}
int AutomatonException::setStateTry(char* stateTry) {
	if (this->stateTry != nullptr) {
		delete[] this->stateTry;
	}
	this->stateTry = new char[strlen(stateTry) + 1];
	strcpy_s(this->stateTry, strlen(stateTry) + 1, stateTry);
	return 0;
}
int AutomatonException::setStateMarked(char* stateMarked) {
	if (this->stateMarked != nullptr) {
		delete[] this->stateMarked;
	}
	this->stateMarked = new char[strlen(stateMarked) + 1];
	strcpy_s(this->stateMarked, strlen(stateMarked) + 1, stateMarked);
	return 0;
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