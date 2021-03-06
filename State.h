#ifndef _STATE_H_
#define _STATE_H_

#include <iostream>
#include <cstring>
#include <string>

const unsigned MAX_NAME_LENGHT = 100;

using std::cout;
using std::cin;

class State
{
public:
	State(const char* = "NoName");
	State(const State&);
	State& operator=(const State&);
	bool operator==(const State&);
	~State();
	int setStateName(char*);
	char* getStateName() const;


private:
	
	char* stateName;
};

std::ostream& operator<<(std::ostream&, const State&);
std::istream& operator>>(std::istream&, State&);

#endif
