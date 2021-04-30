#pragma once
#include <exception>

class AutomatonException:public std::exception{
public:
	AutomatonException(const char* = "No data", const char* ="No data", int = 0, const char* =  "No data", const char*  = "No data", const char* = "No data", const char* = "No data");

	const char* getFile() const;
	int getLine() const;
	const char* getFunc() const;
	const char* getInfo() const;
	const char* getStateTry() const;
	const char* getStateMarked() const;
private:
	const char* file;
	int line;
	const char* func;
	const char* info;
	const char* stateTry;
	const char* stateMarked;
};