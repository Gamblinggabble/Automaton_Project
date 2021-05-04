#pragma once
#include <exception>
#include <iostream>
#include <cstring>
#include <string>

class AutomatonException:public std::exception{
	//AutomatonException a("Error msg", "Wanted entry state", "Current entry state", __FILE__, __LINE__, __FUNCTION__)
public:
	//TODO: Simo - BIGFIVE
	AutomatonException(const char* msg= "No data", const char* stateTry= "No data", const char* stateMarked= "No data", const char* file ="No data", int line = 0, const char*  func= "No data");
	~AutomatonException();
	const char* getFile() const;
	int getLine() const;
	const char* getFunc() const;
	const char* getStateTry() const;
	const char* getStateMarked() const;

	int print() const;
private:
	char* file;
	int line;
	char* func;
	char* stateTry;
	char* stateMarked;
};
std::ostream& operator<<(std::ostream&, AutomatonException&);