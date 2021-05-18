#ifndef DF_AUTOMATON_H
#define DF_AUTOMATON_H

#include "State.h"
#include <iostream>
#include <cstring>
#include <fstream>

template <typename T>
class DFAutomaton
{
public:
	DFAutomaton(unsigned alphabetSize = 0, T* alphabet = nullptr, unsigned statesCnt = 0, State* states = nullptr, const State& entryState = State("NoName"),
		unsigned finalStatesCnt = 0, State* finalStates = nullptr);
	DFAutomaton(const DFAutomaton&);
	~DFAutomaton();

	DFAutomaton& operator=(const DFAutomaton&);

	int setEntryState(char*);
	int setEntryState(State);
	State getEntryState() const;
	unsigned getAlphabetSize() const;
	unsigned getStatesCnt() const;

	int printAlphabet() const; //TODO: help func, could be deleted
	std::ostream& ins(std::ostream&) const;
	std::ofstream& ins(std::ofstream&) const;
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
};

template<typename T>
std::ostream& operator<<(std::ostream&, const DFAutomaton<T>&);
template<typename T>
std::ofstream& operator<<(std::ofstream&, const DFAutomaton<T>&);

template <typename T>
DFAutomaton<T>::DFAutomaton(unsigned alphabetSize, T* alphabet, unsigned statesCnt, State* states, const State& entryState,
	unsigned finalStatesCnt, State* finalStates)
	:statesCnt(statesCnt), states(new State[statesCnt]), entryState(entryState), finalStatesCnt(finalStatesCnt),
	finalStates(new State[finalStatesCnt])
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
		if (typeid(T) == typeid(char)) {
			std::cout << "No alphabet entered! Default alphabet set - {a,b}" << std::endl;
			this->alphabetSize = 2;
			this->alphabet = new T[2]{ 'a', 'b' };
		}
		else {
			std::cout << "No alphabet entered! Default alphabet set - {0,1}" << std::endl;
			this->alphabetSize = 2;
			this->alphabet = new T[2]{ 0, 1 };
		}
	}

	if (states != nullptr) {
		for (unsigned i = 0; i < this->statesCnt; i++)
		{
			this->states[i] = states[i];
		}

		this->entryState = entryState;

		if (finalStates != nullptr) {
			for (unsigned j = 0; j < this->finalStatesCnt; j++)
			{
				this->finalStates[j] = finalStates[j];
			}
		}
		else this->finalStates = nullptr;
	}
	else this->states = nullptr;
}

template <typename T>
DFAutomaton<T>::DFAutomaton(const DFAutomaton<T>& rhs)
	:statesCnt(rhs.statesCnt), states(new State[rhs.statesCnt]), entryState(rhs.entryState), finalStatesCnt(rhs.finalStatesCnt), finalStates(new State[rhs.finalStatesCnt])
{
	if (rhs.alphabet != nullptr) {
		alphabetSize = rhs.alphabetSize;
		if (typeid(T) == typeid(char)) {
			alphabet = new T[alphabetSize + 1];
			for (unsigned i = 0; i <= this->alphabetSize; i++)
			{
				this->alphabet[i] = rhs.alphabet[i];
			}
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
			for (unsigned j = 0; j < this->finalStatesCnt; j++)
			{
				this->finalStates[j] = rhs.finalStates[j];
			}
		}
		else this->finalStates = nullptr;
	}
	else this->states = nullptr;
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
}

template <typename T>
DFAutomaton<T>& DFAutomaton<T>::operator=(const DFAutomaton<T>& rhs) {
	if (this != &rhs) {
		if (rhs.alphabet != nullptr) {
			alphabetSize = rhs.alphabetSize;
			if (typeid(T) == typeid(char)) {
				alphabet = new T[alphabetSize + 1];
				for (unsigned i = 0; i <= this->alphabetSize; i++)
				{
					this->alphabet[i] = rhs.alphabet[i];
				}
			}
			else {
				alphabet = new T[alphabetSize];
				for (unsigned i = 0; i < alphabetSize; i++)
				{
					alphabet[i] = rhs.alphabet[i];
				}
			}
		}
		if (rhs.states != nullptr) {
			this->statesCnt = rhs.statesCnt;
			for (unsigned i = 0; i < this->statesCnt; i++)
			{
				this->states[i] = rhs.states[i];
			}
			
			entryState = rhs.entryState;

			if (rhs.finalStates != nullptr) {
				this->finalStatesCnt = rhs.finalStatesCnt;
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
	}

	return *this;
}

template <typename T>
int DFAutomaton<T>::printAlphabet() const  {
	for (unsigned i = 0; i < alphabetSize; i++)
	{
		std::cout << alphabet[i] << " ";
	}
	return 0;
}

template<typename T>
int DFAutomaton<T>::setEntryState(char* name) {
	entryState = State(name);
	return 0;
}

template<typename T>
int DFAutomaton<T>::setEntryState(State state) {
	entryState = state;
	return 0;
}

template<typename T>
State DFAutomaton<T>::getEntryState() const {
	return entryState;
}

template<typename T>
unsigned DFAutomaton<T>::getAlphabetSize() const {
	return alphabetSize;
}

template<typename T>
unsigned DFAutomaton<T>::getStatesCnt() const {
	return statesCnt;
}

template<typename T>
std::ostream& DFAutomaton<T>::ins(std::ostream& out) const {

	out << "Alphabet: "; 
	for (unsigned i = 0; i < alphabetSize; i++)
	{
		out << alphabet[i] << " ";
	}
	out << std::endl;
	out << "Transition table: "<< std::endl;
	//TODO: print transition table
	out << "Entry state: " << entryState.getStateName() << std::endl;
	out << "Final state" << (finalStatesCnt > 1 ? "s" : "") << ": ";
	for (unsigned i = 0; i < finalStatesCnt; i++)
	{
		out << finalStates[i] << " ";
	}
	out << std::endl;

	return out;
}

template<typename T>
std::ofstream& DFAutomaton<T>::ins(std::ofstream& fout) const {

	fout << "Alphabet: "; 
	for (unsigned i = 0; i < alphabetSize; i++)
	{
		fout << alphabet[i] << " ";
	}
	fout << std::endl;
	fout << "Transition table: " << std::endl;
	//TODO: print transition table
	fout << "Entry state: " << entryState.getStateName() << std::endl;
	fout << "Final state" << (finalStatesCnt>1?"s":"") << ": ";
	for (unsigned i = 0; i < finalStatesCnt; i++)
	{
		fout << finalStates[i] << " ";
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

#endif
