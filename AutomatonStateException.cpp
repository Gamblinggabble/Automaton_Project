#include "AutomatonStateException.h"

AutomatonStateException::AutomatonStateException():std::exception()
{
	file = nullptr;
	fn = nullptr;
	line = 0;
	stateNotFound = "NoState";
}

AutomatonStateException::AutomatonStateException(const State& stateNotFound, const char* file, const char* fn, unsigned line)
:std::exception(), file (new char [strlen(file)+1]),fn (new char [strlen(fn)+1]), stateNotFound (stateNotFound), line (line) 
{
	//we have been using "new" command twice -> once in the initialize list and another one the block
	//this->file = new char[strlen(file) + 1];
	strcpy_s(this->file, strlen(file) + 1, file);

	//this->fn = new char[strlen(fn) + 1];
	strcpy_s(this->fn, strlen(fn) + 1, fn);
}

AutomatonStateException::AutomatonStateException(AutomatonStateException& rhs) : std::exception(rhs) {
	if (rhs.file != nullptr) {
		file = new char[strlen(rhs.file) + 1];
		strcpy_s(file, strlen(rhs.file) + 1, rhs.file);
	}
	else file = nullptr;

	if (rhs.fn != nullptr) {
		fn = new char[strlen(rhs.fn) + 1];
		strcpy_s(fn, strlen(rhs.fn) + 1, rhs.fn);
	}
	else fn = nullptr;

	line = rhs.line;

	stateNotFound = rhs.stateNotFound;

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

const char* AutomatonStateException::what() const noexcept
{
	//TODO: not final state, just state, because this exception is used in the enterying of a transition table
	return "You can't enter this state, because there isn't such a state in the current automaton.";
}


AutomatonStateException::~AutomatonStateException(){

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
	out << std::endl;
	out << "------------------------------------------------------------------------" << std::endl;
	out << rhs.what() << std::endl;
	out << "In file: " << rhs.getFile() << std::endl;
	out << "Function used: " << rhs.getFn() << std::endl;
	out << "Wanted state Not Found: " << rhs.getStateNotFound() << std::endl;
	out << "Line: " << rhs.getLine() << std::endl;
	out << "------------------------------------------------------------------------" << std::endl;
	return out;
}