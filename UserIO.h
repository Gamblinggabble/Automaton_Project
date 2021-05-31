#ifndef USER_IO_H
#define USER_IO_H


#include "DeterminateFiniteAutomaton.h"
#include <iostream>
#include <fstream>
#include <sstream>


int printMenu();
int menu(int option, DFAutomaton<int>& automInt, DFAutomaton<char>& automChar);


int createAutomatConsole(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar);
int createAutomatFile(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar);

int printEntryState(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar);
int changeEntryState(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar);

int printFinalStates(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar);
int printTransitionTable(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar);

int printAutomatOnConsole(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar);
int printAutomatInFile(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar);

int loadSVG(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar);
int readWord(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar);


int clearConsole();

#endif