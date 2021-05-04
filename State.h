#ifndef _STATE_H_
#define _STATE_H_

#include <iostream>
#include <cstring>

using std::cout;
using std::cin;


class State
{
public:
	State(const char* = "NoName");
	State(const State&);
	State& operator=(const State&);
	~State();
	int setStateName(char*);
	char* getStateName()const;


private:
	
	char* stateName;
	

};

std::ostream& operator<<(std::ostream&, State&);

//TODO: Dari - predefined operator >>;
//State s1;

#endif
