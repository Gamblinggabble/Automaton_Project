#ifndef _AUTOMATONSTATEEXCEPTION_H
#define _AUTOMATONSTATEEXCEPTION_H

#include <iostream>
#include <exception>
#include <cstring>
#include <string>
#include "State.h"

class AutomatonStateException :public std::exception {

public:

	AutomatonStateException(const State& stateNotFound, const char* file = "No data", const char* fn = "No data", unsigned line = 0);
	~AutomatonStateException();
	const char* getFile() const;
	const char* getFn() const;
	const State& getStateNotFound() const;
	unsigned getLine() const;
	
private:

	char* file;
	char* fn;
	unsigned line;
	State stateNotFound;
};

std::ostream& operator<<(std::ostream&,const AutomatonStateException&);

#endif