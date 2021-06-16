#ifndef DF_AUTOMATON_H
#define DF_AUTOMATON_H

#include "State.h"
#include "AutomatonStateException.h"
#include "AutomatonException.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <windows.h> 

const unsigned STATE_NAME_SIZE = 31;

template<typename T>
char* cleanCharArr(const char* source) {
	//help function removing the error throwing symbols in char arrays
	unsigned h = 0;
	unsigned sz = strlen(source);
	char* product = new char[sz + 1];
	for (unsigned m = 0; m < sz; m++)
	{
		if ((source[m] >= 'a' && source[m] <= 'z') // a-z
			|| (source[m] >= 'A' && source[m] <= 'Z') // A-Z
			|| (source[m] >= '0' && source[m] <= '9')) // 0-9
		{
			product[h++] = source[m];
		}
	}
	product[h] = '\0';
	return product;
}

template <typename T>
class DFAutomaton
{
public:
	DFAutomaton(unsigned alphabetSize = 0, T* alphabet = nullptr, unsigned statesCnt = 0, State* states = nullptr, State** = nullptr, const State& entryState = State("NoName"),
		unsigned finalStatesCnt = 0, State* finalStates = nullptr);
	DFAutomaton(const DFAutomaton&);
	~DFAutomaton();
	DFAutomaton& operator=(const DFAutomaton&);

	template <typename T> friend  std::istream& operator>>(std::istream&, DFAutomaton<T>&);

	unsigned getAlphabetSize() const;
	T* getAlphabet() const;
	State getEntryState() const;
	unsigned getStatesCnt() const;
	State* getStates() const;
	unsigned getFinalStatesCnt() const;
	State* getFinalStates() const;
	State** getTransitionTable() const;

	int setAlphabetSize(unsigned);
	int setAlphabet(T*);
	int setEntryState(char*);
	int setEntryState(State);
	int setStatesCnt(unsigned);
	int setStates(State*);
	int setFinalStatesCnt(unsigned);
	int setFinalStates(State*);
	int setTransitionTable(State**);

	int printTransitionTable(std::ostream& out) const;
	int printTransitionTable(std::ofstream& out) const;
	std::ostream& ins(std::ostream&) const;
	std::ofstream& ins(std::ofstream&) const;
	std::istream& fillDFAutomaton(std::istream&);
	std::ifstream& fillDFAutomaton(std::ifstream&);
	bool operator()(char* word) const;

	std::string produceSvg() const;
private:
	T* alphabet;
	//number of elements in the alphabet
	//DISCLAMER! if T is of type char, \0 is not counted in alphabetSize
	unsigned alphabetSize;
	unsigned statesCnt;
	State* states;
	//only one entry state can exist
	State entryState;
	//zero or more finalStates
	unsigned finalStatesCnt;
	State* finalStates;
	State** transitionTable;
};

template<typename T>
std::ostream& operator<<(std::ostream&, const DFAutomaton<T>&);
template<typename T>
std::ofstream& operator<<(std::ofstream&, const DFAutomaton<T>&);
template <typename T>
std::istream& operator>>(std::istream&, DFAutomaton<T>&);
template <typename T>
std::ifstream& operator>>(std::ifstream&, DFAutomaton<T>&);


//Big five
template <typename T>
DFAutomaton<T>::DFAutomaton(unsigned alphabetSize, T* alphabet, unsigned statesCnt, State* states, State** transitionTable,
	const State& entryState, unsigned finalStatesCnt, State* finalStates)
	:statesCnt(statesCnt), finalStatesCnt(finalStatesCnt), entryState(entryState)
{
	if (alphabet != nullptr) {
		this->alphabetSize = alphabetSize;
		if (typeid(T) == typeid(char)) {
			this->alphabet = new T[this->alphabetSize + 1];
			// cannot use strcpy_s because a conversion from T* to char* is needed
			for (unsigned i = 0; i <= this->alphabetSize; i++)
			{
				this->alphabet[i] = alphabet[i];
			}
		}
		else {
			this->alphabet = new T[this->alphabetSize];
			for (unsigned i = 0; i < this->alphabetSize; i++)
			{
				this->alphabet[i] = alphabet[i];
			}
		}
	}
	else {
		this->alphabetSize = 0;
		this->alphabet = nullptr;
	}

	if (states != nullptr) {
		this->states = new State[statesCnt];
		for (unsigned i = 0; i < this->statesCnt; i++)
		{
			this->states[i] = states[i];
		}

		if (finalStates != nullptr) {
			finalStates = new State[finalStatesCnt];
			for (unsigned j = 0; j < this->finalStatesCnt; j++)
			{
				this->finalStates[j] = finalStates[j];
			}
		}
		else this->finalStates = nullptr;
	}
	else {
		this->states = nullptr;
		this->finalStates = nullptr;
	}

	//set transition table
	if (transitionTable != nullptr) {
		//create transition table
		this->transitionTable = new State * [this->statesCnt];
		for (unsigned i = 0; i < this->statesCnt; i++) {
			this->transitionTable[i] = new State[this->alphabetSize];
		}
		//fill transition table
		for (unsigned r = 0; r < this->statesCnt; r++) {
			for (unsigned c = 0; c < this->alphabetSize; c++) {
				this->transitionTable[r][c] = transitionTable[r][c];
			}
		}
	}
	else this->transitionTable = nullptr;
}

template <typename T>
DFAutomaton<T>::DFAutomaton(const DFAutomaton<T>& rhs)
	:statesCnt(rhs.statesCnt), states(new State[rhs.statesCnt]), entryState(rhs.entryState), finalStatesCnt(rhs.finalStatesCnt)
{
	if (rhs.alphabet != nullptr) {
		alphabetSize = rhs.alphabetSize;
		if (typeid(T) == typeid(char)) {
			alphabet = new T[alphabetSize + 1];
			for (unsigned i = 0; i < this->alphabetSize; i++)
			{
				this->alphabet[i] = rhs.alphabet[i];
			}
			alphabet[alphabetSize] = '\0';
		}
		else {
			alphabet = new T[alphabetSize];
			for (unsigned i = 0; i < alphabetSize; i++)
			{
				alphabet[i] = rhs.alphabet[i];
			}
		}
	}
	else {
		alphabetSize = 0;
		alphabet = nullptr;
	}

	if (rhs.states != nullptr) {
		for (unsigned i = 0; i < this->statesCnt; i++)
		{
			this->states[i] = rhs.states[i];
		}

		entryState = rhs.entryState;

		if (rhs.finalStates != nullptr) {
			finalStates = new State[rhs.finalStatesCnt];
			for (unsigned j = 0; j < this->finalStatesCnt; j++)
			{
				this->finalStates[j] = rhs.finalStates[j];
			}
		}
		else {
			this->finalStatesCnt = 0;
			this->finalStates = nullptr;
		}
	}
	else {
		this->statesCnt = 0;
		this->states = nullptr;
	}

	//set transition table
	if (rhs.transitionTable != nullptr) {

		//create transition table
		transitionTable = new State * [statesCnt];
		for (unsigned i = 0; i < statesCnt; i++) {
			transitionTable[i] = new State[alphabetSize];
		}

		//fill transition table
		for (unsigned r = 0; r < statesCnt; r++) {
			for (unsigned c = 0; c < alphabetSize; c++) {
				transitionTable[r][c] = rhs.transitionTable[r][c];
			}
		}
	}
	else transitionTable = nullptr;
}

template <typename T>
DFAutomaton<T>::~DFAutomaton() {
	if (alphabet != nullptr) {
		delete[] alphabet;
	}
	if (finalStates != nullptr) {
		delete[] finalStates;
	}
	if (states != nullptr) {
		delete[] states;
	}

	if (transitionTable != nullptr) {
		for (unsigned i = 0; i < statesCnt; i++) {
			delete[] transitionTable[i];
		}
		delete[] transitionTable;
	}
}

template <typename T>
DFAutomaton<T>& DFAutomaton<T>::operator=(const DFAutomaton<T>& rhs) {
	if (this != &rhs) {
		// delete transition table if initialized
		//!!!must be done here, before changing the value of statesCnt
		if (transitionTable != nullptr) {
			for (unsigned i = 0; i < statesCnt; i++) {
				delete[] transitionTable[i];
			}
			delete[] transitionTable;
			transitionTable = nullptr;
		}

		//set alphabet
		if (rhs.alphabet != nullptr) {

			if (alphabet != nullptr) {
				delete[] this->alphabet;
			}

			alphabetSize = rhs.alphabetSize;
			if (typeid(T) == typeid(char)) {
				alphabet = new T[alphabetSize + 1];
				for (unsigned i = 0; i < this->alphabetSize; i++)
				{
					this->alphabet[i] = rhs.alphabet[i];
				}
				alphabet[alphabetSize] = '\0';
			}
			else {
				alphabet = new T[alphabetSize];
				for (unsigned i = 0; i < alphabetSize; i++)
				{
					alphabet[i] = rhs.alphabet[i];
				}
			}
		}
		else {
			this->alphabetSize = 0;
			this->alphabet = nullptr;
		}

		//set states
		if (rhs.states != nullptr) {
			this->statesCnt = rhs.statesCnt;
			if (this->states != nullptr) {
				delete[] this->states;
			}
			this->states = new State[this->statesCnt];
			for (unsigned i = 0; i < this->statesCnt; i++)
			{
				this->states[i] = rhs.states[i];
			}

			entryState = rhs.entryState;

			if (rhs.finalStates != nullptr) {
				this->finalStatesCnt = rhs.finalStatesCnt;
				if (this->finalStates != nullptr) {
					delete[] this->finalStates;
				}
				this->finalStates = new State[this->finalStatesCnt];
				for (unsigned i = 0; i < this->finalStatesCnt; i++)
				{
					this->finalStates[i] = rhs.finalStates[i];
				}
			}
			else {
				this->finalStatesCnt = 0;
				this->finalStates = nullptr;
			}
		}
		else {
			this->statesCnt = 0;
			this->states = nullptr;
		}

		//set transition table
		if (rhs.transitionTable != nullptr) {

			//create new
			transitionTable = new State * [statesCnt];
			for (unsigned i = 0; i < statesCnt; i++) {
				transitionTable[i] = new State[alphabetSize];
			}

			//fill transitionTable
			for (unsigned r = 0; r < statesCnt; r++) {
				for (unsigned c = 0; c < alphabetSize; c++) {
					transitionTable[r][c] = rhs.transitionTable[r][c];
				}
			}
		}
		else transitionTable = nullptr;
	}

	return *this;
}

//getters
template<typename T>
unsigned DFAutomaton<T>::getAlphabetSize() const {
	return alphabetSize;
}
template<typename T>
T* DFAutomaton<T>::getAlphabet() const {
	return alphabet;
}
template<typename T>
State DFAutomaton<T>::getEntryState() const {
	return entryState;
}
template<typename T>
unsigned DFAutomaton<T>::getStatesCnt() const {
	return statesCnt;
}
template<typename T>
State* DFAutomaton<T>::getStates() const {
	return states;
}
template<typename T>
unsigned DFAutomaton<T>::getFinalStatesCnt() const {
	return finalStatesCnt;
}
template<typename T>
State* DFAutomaton<T>::getFinalStates() const {
	return finalStates;
}
template<typename T>
State** DFAutomaton<T>::getTransitionTable() const {
	return transitionTable;
}

//setters
template<typename T>
int DFAutomaton<T>::setAlphabetSize(unsigned alphabetSize) {
	this->alphabetSize = alphabetSize;
	return 0;
}
template<typename T>
int DFAutomaton<T>::setAlphabet(T* alphabet) {
	if (this->alphabet != nullptr) {
		delete[] this->alphabet;
	}
	if (typeid(T) == typeid(char)) {
		this->alphabet = new T[alphabetSize + 1];
		for (unsigned i = 0; i < alphabetSize; i++) {
			this->alphabet[i] = alphabet[i];
		}
		this->alphabet[alphabetSize] = '\0';
	}
	else {
		this->alphabet = new T[alphabetSize];
		for (unsigned i = 0; i < alphabetSize; i++) {
			this->alphabet[i] = alphabet[i];
		}
	}
	return 0;
}
template<typename T>
int DFAutomaton<T>::setEntryState(char* name) {
	//entryState = State(name);
	int i = 0;
	char nameInput[STATE_NAME_SIZE];
	char leftInput[STATE_NAME_SIZE];
	while (name[i] != ' ' && name[i] != '\0') {
		nameInput[i] = name[i];
		i++;
	}
	nameInput[i] = '\0';
	bool isLeft = false;
	int k = 0;
	while (name[i] != '\0') {
		isLeft = true;
		if (name[i] != ' ') {
			leftInput[k] = name[i];
			k++;
			if (name[i + 1] == ' ') break;
		}
		i++;
	}
	leftInput[k] = '\0';

	bool stateFlag = false;
	for (unsigned k = 0; k < statesCnt; k++) {
		if (strcmp(nameInput, states[k].getStateName()) == 0) {
			stateFlag = true;
			entryState = State(nameInput);
			break;
		}
	}
	if (!stateFlag) {
		AutomatonStateException stateNotExist(State(nameInput), __FILE__, __FUNCTION__, __LINE__);
		throw stateNotExist;
	}
	if (isLeft) {
		AutomatonException onlyOneState("Exception: Only one entry state could be entered!", leftInput, entryState.getStateName(), __FILE__, __LINE__, __FUNCTION__);
		throw onlyOneState;
	}

	//q1 q2 q3
	return 0;
}


template<typename T>
int DFAutomaton<T>::setEntryState(State state) {
	setEntryState(state.getStateName());
	return 0;
}
template<typename T>
int DFAutomaton<T>::setStatesCnt(unsigned number) {
	statesCnt = number;
	return 0;
}
template<typename T>
int DFAutomaton<T>::setStates(State* states) {
	if (this->states != nullptr) {
		delete[] this->states;
	}
	this->states = new State[statesCnt];
	for (unsigned i = 0; i < statesCnt; i++) {
		this->states[i] = states[i];
	}
	return 0;
}
template<typename T>
int DFAutomaton<T>::setFinalStatesCnt(unsigned finalStatesCnt) {
	this->finalStatesCnt = finalStatesCnt;
	return 0;
}
template<typename T>
int DFAutomaton<T>::setFinalStates(State* finalStates) {
	if (this->finalStates != nullptr) {
		delete[] this->finalStates;
	}
	this->finalStates = new State[finalStatesCnt];
	for (unsigned i = 0; i < finalStatesCnt; i++) {
		this->finalStates[i] = finalStates[i];
	}
	return 0;
}
template<typename T>
int DFAutomaton<T>::setTransitionTable(State** transitionTable) {
	if (this->transitionTable != nullptr) {
		for (unsigned i = 0; i < statesCnt; i++) {
			delete[] this->transitionTable[i];
		}
		delete[] this->transitionTable;
	}
	this->transitionTable = new State * [statesCnt];
	for (unsigned i = 0; i < statesCnt; i++) {
		this->transitionTable[i] = new State[alphabetSize];
		for (unsigned j = 0; j < alphabetSize; j++) {
			this->transitionTable[i][j] = transitionTable[i][j];
		}
	}
	return 0;
}


//printing functions
template<typename T>
int DFAutomaton<T>::printTransitionTable(std::ostream& out) const
{
	if (transitionTable != nullptr) {
		//finds the longest state name
		unsigned SETW_PARAM = strlen(states[0].getStateName());
		for (unsigned i = 0; i < statesCnt; i++)
		{
			if (SETW_PARAM < strlen(states[i].getStateName()))
				SETW_PARAM = strlen(states[i].getStateName());
		}
		SETW_PARAM += 2;

		out << "Transition table: " << std::endl << std::endl;
		cout << std::setw(SETW_PARAM) << "";
		for (unsigned i = 0; i < alphabetSize; i++)
		{
			cout << std::setw(SETW_PARAM) << alphabet[i];
		}
		cout << std::endl << std::endl;
		for (unsigned i = 0; i < statesCnt; i++)
		{
			cout << std::setw(SETW_PARAM) << states[i];

			for (unsigned j = 0; j < alphabetSize; j++)
			{
				cout << std::setw(SETW_PARAM) << transitionTable[i][j];
			}
			cout << std::endl;
		}
	}
	else {
		out << "Transition table: not entered" << std::endl;
	}
	return 0;
}
template<typename T>
int DFAutomaton<T>::printTransitionTable(std::ofstream& out) const {

	if (transitionTable != nullptr) {

		for (unsigned i = 0; i < statesCnt; i++)
		{
			for (unsigned j = 0; j < alphabetSize; j++)
			{
				out << transitionTable[i][j] << " ";
			}
			out << std::endl;
		}
	}
	else {
		out << "Transition table: not entered" << std::endl;
	}
	return 0;
}
template<typename T>
std::ostream& DFAutomaton<T>::ins(std::ostream& out) const {

	out << "Alphabet: ";
	for (unsigned i = 0; i < alphabetSize; i++)
	{
		out << alphabet[i] << " ";
	}
	out << std::endl;

	printTransitionTable(out);
	out << std::endl;

	out << "Entry state: " << entryState << std::endl;
	out << "Final state" << (finalStatesCnt == 1 ? "" : "s") << ": ";
	if (finalStatesCnt == 0) out << "none";
	for (unsigned i = 0; i < finalStatesCnt; i++)
	{
		out << finalStates[i] << " ";
	}
	out << std::endl;

	return out;
}
template<typename T>
std::ofstream& DFAutomaton<T>::ins(std::ofstream& fout) const {
	//prints alphabet type char/int
	fout << (typeid(T) == typeid(char) ? 2 : 1) << std::endl;
	//prints states
	fout << statesCnt;
	for (unsigned i = 0; i < statesCnt; i++)
	{
		fout << " " << states[i];
	}
	fout << std::endl;
	//prints alphabet
	fout << alphabetSize;
	for (unsigned i = 0; i < alphabetSize; i++)
	{
		fout << " " << alphabet[i];
	}
	fout << std::endl;
	//prints transition table
	printTransitionTable(fout);
	//prints entry state
	fout << entryState << std::endl;
	//prints final states
	fout << finalStatesCnt;
	for (unsigned i = 0; i < finalStatesCnt; i++)
	{
		fout << " " << finalStates[i];
	}
	fout << std::endl;

	return fout;
}
template<typename T>
std::ostream& operator<<(std::ostream& lhs, const DFAutomaton<T>& rhs) {
	return rhs.ins(lhs);
}
template<typename T>
std::ofstream& operator<<(std::ofstream& lhs, const DFAutomaton<T>& rhs) {
	return rhs.ins(lhs);
}

//inserting functions
template<typename T>
std::istream& DFAutomaton<T>::fillDFAutomaton(std::istream& in) {

	//delete current transition table
	// !!! must be done here, before changing the value of statesCnt
	if (transitionTable != nullptr) {
		for (unsigned i = 0; i < statesCnt; i++) {
			delete[] transitionTable[i];
		}
		delete[] transitionTable;
		transitionTable = nullptr;
	}

	//number of states
	std::cout << "Please enter number of states: ";
	in >> statesCnt;

	//states
	if (states != nullptr) {
		delete[] states;
	}
	states = new State[statesCnt];
	for (unsigned i = 0; i < statesCnt; i++) {
		std::cout << "Please enter state [" << i + 1 << "]: ";
		in >> states[i];
	}

	//number of elements in the alphabet
	std::cout << "Please enter number of symbols in the alphabet: ";
	in >> alphabetSize;

	//enter elements of alphabet
	if (alphabet != nullptr) {
		delete[] alphabet;
	}
	if (typeid(T) == typeid(char)) {
		alphabet = new T[alphabetSize + 1];

		for (unsigned i = 0; i < alphabetSize; i++) {
			std::cout << "Please enter symbol number [" << i + 1 << "]: ";
			in >> alphabet[i];
		}
		alphabet[alphabetSize] = '\0';
	}
	else {

		alphabet = new T[alphabetSize];

		for (unsigned i = 0; i < alphabetSize; i++) {
			std::cout << "Please enter symbol number [" << i + 1 << "]: ";
			in >> alphabet[i];
		}
	}


	//initialize a new transition table with entered size values
	transitionTable = new State * [statesCnt];
	for (unsigned i = 0; i < statesCnt; i++) {
		transitionTable[i] = new State[alphabetSize];
	}

	//enter transition table
	for (unsigned i = 0; i < statesCnt; i++) {
		for (unsigned j = 0; j < alphabetSize; j++) {
			//check the input
			bool inputTransitionCheck = false;

			while (!inputTransitionCheck) {
				try {
					std::cout << "Please enter (" << states[i] << "," << alphabet[j] << "): ";
					in >> transitionTable[i][j];
					for (unsigned k = 0; k < statesCnt; k++) {
						if (strcmp(states[k].getStateName(), transitionTable[i][j].getStateName()) == 0) {
							inputTransitionCheck = true;
							break;
						}
					}
					if (!inputTransitionCheck) {
						AutomatonStateException eTT(transitionTable[i][j], __FILE__, __FUNCTION__, __LINE__);
						throw eTT;
					}
				}
				catch (AutomatonStateException eTT) {
					cout << eTT;
				}
			}
		}
	}
	//enter entry state
	std::cout << "Please enter an entry state: ";
	//in >> entryState;
	bool isStateAlright = false;
	char input[STATE_NAME_SIZE];
	//in.clear();
	char dummy[STATE_NAME_SIZE];
	in.getline(dummy, STATE_NAME_SIZE);
	//in.ignore();
	in.getline(input, STATE_NAME_SIZE);
	while (!isStateAlright) {
		try {
			setEntryState(input);
			isStateAlright = true;
		}
		catch (AutomatonStateException ex1) {
			std::cout << ex1;
			std::cout << std::endl;
			std::cout << "Please enter another entry state: ";
			in.getline(input, STATE_NAME_SIZE);
		}
		catch (AutomatonException ex2) {
			std::cout << ex2;
			std::cout << std::endl;
			break;
		}
	}


	//enter number of final states
	std::cout << "Please enter the number of final states: ";
	in >> finalStatesCnt;

	//delete old final states array and create a new one
	if (finalStates != nullptr) {
		delete[] finalStates;
	}
	finalStates = new State[finalStatesCnt];

	//enter final states
	for (unsigned i = 0; i < finalStatesCnt; i++) {
		std::cout << "Enter final state number [" << i + 1 << "]: ";
		in >> finalStates[i];
		bool stateFlag = false;
		while (!stateFlag) {
			try {
				for (unsigned k = 0; k < statesCnt; k++) {
					if (strcmp(finalStates[i].getStateName(), states[k].getStateName()) == 0) {
						stateFlag = true;
						break;
					}
				}
				if (!stateFlag) {
					//std::cout << "You can't enter this final state, because there isn't such a state in the current automaton. Please enter another one: ";
					//in >> finalStates[i];
					AutomatonStateException stateEx1(finalStates[i], __FILE__, __FUNCTION__, __LINE__);
					throw stateEx1;
					//? confused about which function to call - copy constructor or constructor with parameters
				}
			}
			catch (AutomatonStateException stateEx) {
				std::cout << std::endl;
				cout << stateEx;
				std::cout << "Please enter another state: ";
				in >> finalStates[i];
				//изтрива състояние
			}
		}
	}

	return in;
}
template<typename T>
std::ifstream& DFAutomaton<T>::fillDFAutomaton(std::ifstream& in) {
	//deleting the old TT and intializing TT with new data
	// !!! must to be done here, before changing the value of statesCnt
	if (transitionTable != nullptr) {
		for (unsigned i = 0; i < statesCnt; i++) {
			delete[] transitionTable[i];
		}
		delete[] transitionTable;
		transitionTable = nullptr;
	}

	//number of states
	in >> statesCnt;
	//the states
	if (states != nullptr) {
		delete[]states;
	}
	states = new State[statesCnt];
	for (unsigned i = 0; i < statesCnt; i++) {
		in >> states[i];
	}

	//number of alphabet symbols
	in >> alphabetSize;

	//adding el from the alphabet
	if (alphabet != nullptr) {
		delete[] alphabet;
	}

	if (typeid(T) == typeid(char)) {
		alphabet = new T[alphabetSize + 1];

		for (unsigned i = 0; i < alphabetSize; i++) {
			in >> alphabet[i];
		}
		alphabet[alphabetSize] = '\0';
	}
	else {
		alphabet = new T[alphabetSize];

		for (unsigned i = 0; i < alphabetSize; i++) {
			in >> alphabet[i];
		}
	}

	//reserving space for the TT
	transitionTable = new State * [statesCnt];
	for (unsigned i = 0; i < statesCnt; i++) {
		transitionTable[i] = new State[alphabetSize];
	}

	//insert transition table
	for (unsigned i = 0; i < statesCnt; i++) {
		for (unsigned j = 0; j < alphabetSize; j++) {
			in >> transitionTable[i][j];
			//check the input
			bool inputTransitionCheck = false;
			while (!inputTransitionCheck) {
				for (unsigned k = 0; k < statesCnt; k++) {
					if (strcmp(states[k].getStateName(), transitionTable[i][j].getStateName()) == 0) inputTransitionCheck = true;
				}
				if (!inputTransitionCheck) {
					std::cout << "There isn't such a state in the current automaton. Corrupted Automaton!";
					return in;
				}
			}
		}
	}

	//add entry state
	in >> entryState;
	bool stateFlag = false;
	while (!stateFlag) {
		for (unsigned h = 0; h < statesCnt; h++) {
			if (strcmp(entryState.getStateName(), states[h].getStateName()) == 0) stateFlag = true;
		}
		if (!stateFlag) {
			//TODO: handle exception or don't
			std::cout << "Invalid entry state! Corrupted Automaton!";
			in.close();
			exit(0);
		}
	}

	//enter number of final states
	in >> finalStatesCnt;

	//deletion of the old array with final states and creating new
	if (finalStates != nullptr) {
		delete[] finalStates;
	}
	finalStates = new State[finalStatesCnt];

	//enter final states
	for (unsigned i = 0; i < finalStatesCnt; i++) {

		in >> finalStates[i];
		stateFlag = false;
		while (!stateFlag) {
			for (unsigned h = 0; h < statesCnt; h++) {
				if (strcmp(finalStates[i].getStateName(), states[h].getStateName()) == 0) stateFlag = true;
			}
			if (!stateFlag) {
				//in case final state isn't a valid state
				std::cout << "Invalid final state! Corrupted Automaton!";
				return in;
			}
		}
	}

	return in;
}
template <typename T>
std::istream& operator>>(std::istream& in, DFAutomaton<T>& rhs) {
	return rhs.fillDFAutomaton(in);
}
template <typename T>
std::ifstream& operator>>(std::ifstream& in, DFAutomaton<T>& rhs) {
	return rhs.fillDFAutomaton(in);
}


//reading a word
template <typename T>
bool DFAutomaton<T>::operator()(char* word) const {

	unsigned i = 0;
	State currentState = entryState;
	unsigned currentStateIndex = 0;

	while (word[i] != '\0') {

		bool isThere = false;
		for (unsigned a = 0; a < alphabetSize; a++) {

			if (typeid(T) == typeid(char) && word[i] == alphabet[a]) {
				isThere = true;
				currentState = transitionTable[currentStateIndex][a];
				break;
			}
			else if (typeid(T) == typeid(int) && (word[i] - '0') == alphabet[a]) {
				isThere = true;
				currentState = transitionTable[currentStateIndex][a];
				break;
			}
		}
		if (isThere) {
			for (unsigned s = 0; s < statesCnt; s++) {
				if (states[s] == currentState) {
					currentStateIndex = s;
					break;
				}
			}
		}
		else return false;

		i++;
	}
	for (unsigned s = 0; s < finalStatesCnt; s++) {
		if (currentState == finalStates[s]) {
			return true;
		}
	}

	return false;
}


//SVG creator 
template<typename T>
std::string DFAutomaton<T>::produceSvg() const {

	std::stringstream dotParser;
	dotParser << "node[shape=doublecircle];%20";
	for (unsigned i = 0; i < finalStatesCnt; i++)
	{
		char* tmp = cleanCharArr<T>(finalStates[i].getStateName());
		dotParser << tmp << "%20";
		if (tmp != nullptr) delete[] tmp;
	}
	dotParser << "%0Anode[shape=circle];%0A";
	//color of entry state node: lightgreen
	//dotParser << entryState.getStateName() << "[style=filled,fillcolor=lightgreen];%0A";
	//color of entry state node: lightblue
	char* tmp = cleanCharArr<T>(entryState.getStateName());
	dotParser << tmp << "[style=filled,fillcolor=%22%23b3ffff%22];%0A";
	if (tmp != nullptr) delete[] tmp;
	for (unsigned i = 0; i < statesCnt; i++)
	{
		for (unsigned j = 0; j < alphabetSize; j++)
		{
			char transitionSymbols[10];
			int g = 0;
			bool nextExist = false;
			for (unsigned k = j + 1; k < alphabetSize; k++)
			{
				if (strcmp(transitionTable[i][j].getStateName(), transitionTable[i][k].getStateName()) == 0) {
					nextExist = true;
					break;
				}
			}
			if (!nextExist) {
				for (unsigned k = 0; k < alphabetSize; k++)
				{
					if (strcmp(transitionTable[i][j].getStateName(), transitionTable[i][k].getStateName()) == 0) {
						if (typeid(T) == typeid(int))
							transitionSymbols[g++] = alphabet[k] + '0';
						else if (typeid(T) == typeid(char))
							transitionSymbols[g++] = alphabet[k];
					}
				}
				transitionSymbols[g++] = '\0';
			}
			else {
				continue;
			}

			char* firstStateName = cleanCharArr<T>(states[i].getStateName());
			char* secondStateName = cleanCharArr<T>(transitionTable[i][j].getStateName());
			dotParser << firstStateName << "%20-%3E%20" << secondStateName << "[label%3D%22";
			//dotParser << states[i].getStateName() << "%20-%3E%20" << transitionTable[i][j].getStateName() << "[label%3D%22";
			for (unsigned h = 0; h < g - 1; h++)
			{
				dotParser << transitionSymbols[h];
				if (h != g - 2) {
					dotParser << "%2C";
				}
			}
			dotParser << "%22];%0A";

			if (firstStateName != nullptr) delete[] firstStateName;
			if (secondStateName != nullptr) delete[] secondStateName;
		}
	}
	dotParser << '}';


	//dot syntax
	/*{
	node [shape = doublecircle]; a d;
	node [shape = circle];
	a [ style = "filled" fillcolor = "lightgreen"]
	a -> b [label="1"]
	b -> a [label="0,1"]
	a -> c
	a -> a
	d -> d
	}*/


	std::string preText = dotParser.str();
	return preText;
}

#endif
