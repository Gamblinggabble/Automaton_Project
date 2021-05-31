#ifndef _AUTOMATON_STATE_EXCEPTION_H
#define _AUTOMATON_STATE_EXCEPTION_H

#include <iostream>
#include <exception>
#include <cstring>
#include <string>
#include "State.h"

class AutomatonStateException :public std::exception {

public:
	AutomatonStateException();
	AutomatonStateException(const State& stateNotFound, const char* file = "No data", const char* fn = "No data", unsigned line = 0);
	AutomatonStateException(AutomatonStateException&);
	virtual ~AutomatonStateException();

	AutomatonStateException& operator=(const AutomatonStateException&);
	const char* what() const noexcept;
	const char* getFile() const;
	const char* getFn() const;
	const State& getStateNotFound() const;
	unsigned getLine() const;
	//Dari TODO: add setters
private:

	char* file;
	char* fn;
	unsigned line;
	State stateNotFound;
};

std::ostream& operator<<(std::ostream&,const AutomatonStateException&);

#endif
