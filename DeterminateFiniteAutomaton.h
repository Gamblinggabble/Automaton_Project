#ifndef DF_AUTOMATON_H
#define DF_AUTOMATON_H

#include "State.h"
#include <iostream>
#include <cstring>

template <typename T>
class DFAutomaton
{
public:
	DFAutomaton(unsigned alphabetSize = 0, T* alphabet = nullptr, unsigned statesCnt = 0, State* states = nullptr, const State& entryState = NULL,
		unsigned finalStatesCnt = 0, State* finalStates = nullptr);
	DFAutomaton(const DFAutomaton&);
	~DFAutomaton();

	DFAutomaton& operator=(const DFAutomaton&);

	int setEntryState(char*);
	int setEntryState(State);
	State getEntryState() const;

	int printAlphabet();
private:
	T* alphabet;
	unsigned alphabetSize;

	unsigned statesCnt;
	State* states;
	//only one entry state can exist
	State entryState;
	//zero or more finalStates
	unsigned finalStatesCnt;
	State* finalStates;
};


template <typename T>
DFAutomaton<T>::DFAutomaton(unsigned alphabetSize, T* alphabet, unsigned statesCnt, State* states, const State& entryState,
	unsigned finalStatesCnt, State* finalStates)
	:statesCnt(statesCnt), states(new State[statesCnt]), entryState(entryState), finalStatesCnt(finalStatesCnt),
	finalStates(new State[finalStatesCnt])
{
	if (alphabet != nullptr) {
		this->alphabetSize = alphabetSize;
		this->alphabet = new T[alphabetSize];
		for (unsigned i = 0; i < alphabetSize; i++)
		{
			this->alphabet[i] = alphabet[i];
		}
	}
	else {
		std::cout << "No alphabet entered! Default alphabet set - {0,1}" << std::endl;
		this->alphabetSize = 2;
		this->alphabet = new T[2]{ 0, 1 };
	}

	if (states != nullptr) {
		for (unsigned i = 0; i < this->statesCnt; i++)
		{
			this->states[i] = states[i];
		}

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
		alphabet = new T[alphabetSize];
		for (unsigned i = 0; i < alphabetSize; i++)
		{
			alphabet[i] = rhs.alphabet[i];
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
			alphabet = new T[alphabetSize];
			for (unsigned i = 0; i < alphabetSize; i++)
			{
				alphabet[i] = rhs.alphabet[i];
			}
		}
		if (rhs.states != nullptr) {
			this->statesCnt = rhs.statesCnt;
			for (unsigned i = 0; i < this->statesCnt; i++)
			{
				this->states[i] = rhs.states[i];
			}

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
int DFAutomaton<T>::printAlphabet() {
	for (unsigned i = 0; i < alphabetSize; i++)
	{
		std::cout << alphabet[i] << " ";
	}
	return 0;
}

/*В случай, че едно състояние на автомата е маркирано като начално е необходимо
при опит да се маркира второ състояние за начално да се изхвърля и обработва изключение
от потребителски дефиниран клас AutomatonException. Той наследява стандартния клас
за изключения и предоставя механизми за описание на ред от кода, който предизвиква
грешката, както и име на състоянието, което се опитваме да направим начално и име на
състоянието, което вече е маркирано като начално.*/
/*
* Автоматът трябва да има член-функция, която ясно показва на потребителя текущото
начално състояние и позволява то да се смени, като се размаркира като начално, а на негово
място потребителят посочва ново начално състояние.
*/
template<typename T>
int DFAutomaton<T>::setEntryState(char* name) {

	return 0;
}

template<typename T>
int DFAutomaton<T>::setEntryState(State state) {


	return 0;
}

template<typename T>
State DFAutomaton<T>::getEntryState() const {
	return entryState;
}

#endif
