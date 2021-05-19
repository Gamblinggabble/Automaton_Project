#ifndef DF_AUTOMATON_H
#define DF_AUTOMATON_H

#include "State.h"
#include <iostream>
#include <cstring>

template <typename T>
class DFAutomaton
{
public:
	DFAutomaton(unsigned alphabetSize = 0, T* alphabet = nullptr, unsigned statesCnt = 0, State* states = nullptr, State** = nullptr, const State& entryState = State("NoName"),
		unsigned finalStatesCnt = 0, State* finalStates = nullptr);
	DFAutomaton(const DFAutomaton&);
	~DFAutomaton();

	DFAutomaton& operator=(const DFAutomaton&);

	int setEntryState(char*);
	int setEntryState(State);
	State getEntryState() const;
	unsigned getAlphabetSize() const;
	unsigned getStatesCnt() const;
	State* getStates() const;
	T* getAlphabet() const;

	int printAlphabet();
	int fillDFAutomatonConsole();
	std::ifstream& fillDFAutomaton(std::ifstream&);
private:
	T* alphabet;
	unsigned alphabetSize;

	unsigned statesCnt;
	State* states;
	//only one entry state can exist
	State** transitionTable;
	State entryState;
	//zero or more finalStates
	unsigned finalStatesCnt;
	State* finalStates;
};

template <typename T>
std::istream& operator>>(std::istream& in, DFAutomaton<T>& rhs) {
	rhs.fillDFAutomaton(in);
	return in;
}

template <typename T>
std::ifstream& operator>>(std::ifstream& in, DFAutomaton<T>& rhs) {
	rhs.fillDFAutomaton(in);
	return in;
}

template <typename T>
DFAutomaton<T>::DFAutomaton(unsigned alphabetSize, T* alphabet, unsigned statesCnt, State* states, State** transitionTable, const State& entryState,
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

		if (finalStates != nullptr) { //Симо - според мен тази функция трябва да е извън блока на горната
			for (unsigned j = 0; j < this->finalStatesCnt; j++)
			{
				this->finalStates[j] = finalStates[j];
			}
		}
		else this->finalStates = nullptr;
	}
	else this->states = nullptr;


	//добавяне на transition table
	if (transitionTable != nullptr) {
		//деклариране
		this->transitionTable = new State * [this->statesCnt];
		for (int i = 0; i < this->statesCnt; i++) {
			this->transitionTable[i] = new State[this->alphabetSize];
		}
		//инициализиране/ копиране от параметъра
		for (int r = 0; r < this->statesCnt; r++) {
			for (int c = 0; c < this->alphabetSize; c++) {
				this->transitionTable[r][c] = transitionTable[r][c];
			}
		}
	}
	else this->transitionTable = nullptr;
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

	//добавяне на transition table
	//размерите вече са присвоени от горните редове код, поради което осъществяваме само копиране
	if (rhs.transitionTable != nullptr) {
		//трием старата таблица
		for (int i = 0; i < statesCnt; i++) {
			delete[] transitionTable[i];
		}
		delete[] transitionTable;

		//създаваме нова
		transitionTable = new State * [statesCnt];
		for (int i = 0; i < statesCnt; i++) {
			transitionTable[i] = new State[alphabetSize];
		}

		//копираме елементите от таблицата на единия автомат в таблицата на другия
		for (int r = 0; r < statesCnt; r++) {
			for (int c = 0; c < alphabetSize; c++) {
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

	//изтриваме transition table
	if (transitionTable != nullptr) {
		for (int i = 0; i < statesCnt; i++) {
			delete[] transitionTable[i];
		}
		delete[] transitionTable;
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

		//добавяне на transition table
		if (rhs.transitionTable != nullptr) {
			//трием старата таблица
			for (int i = 0; i < statesCnt; i++) {
				delete[] transitionTable[i];
			}
			delete[] transitionTable;

			//създаваме нова
			transitionTable = new State * [statesCnt];
			for (int i = 0; i < statesCnt; i++) {
				transitionTable[i] = new State[alphabetSize];
			}

			//копираме елементите от таблицата на единия автомат в таблицата на другия
			for (int r = 0; r < statesCnt; r++) {
				for (int c = 0; c < alphabetSize; c++) {
					transitionTable[r][c] = rhs.transitionTable[r][c];
				}
			}
		}
		else transitionTable = nullptr;

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

template<typename T>
unsigned DFAutomaton<T>::getAlphabetSize() const {
	return alphabetSize;
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
T* DFAutomaton<T>::getAlphabet() const {
	return alphabet;
}

template<typename T>
int DFAutomaton<T>::fillDFAutomatonConsole() {
	//брой състояния
	std::cout << "Please enter number of states: ";
	std::cin >> statesCnt;
	//състоянията
	if (states != nullptr) {
		delete[]states;
	}
	states = new State[statesCnt];
	for (int i = 0; i < statesCnt; i++) {
		std::cout << "Please enter state [" << i + 1 << "]: ";
		std::cin >> states[i];
	}

	//брой елементи в азбуката
	std::cout << "Please enter number of symbols in the alphabet: ";
	std::cin >> alphabetSize;

	//въвеждане на елементите на азбуката
	if (alphabet != nullptr) {
		delete[] alphabet;
	}
	alphabet = new T[alphabetSize];

	for (int i = 0; i < alphabetSize; i++) {
		std::cout << "Please enter symbol number [" << i + 1 << "]: ";
		std::cin >> alphabet[i];
	}

	//изтриване на старата таблица и инициализация на transition table с новите данни
	if (transitionTable != nullptr) {
		for (int i = 0; i < statesCnt; i++) {
			delete[] transitionTable[i];
		}
		delete[] transitionTable;
	}
	
	transitionTable = new State * [statesCnt];
	for (int i = 0; i < statesCnt; i++) {
		transitionTable[i] = new State[alphabetSize];
	}

	//TODO Въвеждаме transition table
	for (int i = 0; i < statesCnt; i++) {
		for (int j = 0; j < alphabetSize; j++) {
			std::cout << "Please enter (" << states[i] << "," << alphabet[j] << "): ";
			std::cin >> transitionTable[i][j];
			//TODO Проверка на входа
			bool inputTransitionCheck = false;
			while (!inputTransitionCheck) {
				for (int k = 0; k < statesCnt; k++) {
					if (strcmp(states[k].getStateName(), transitionTable[i][j].getStateName()) == 0) inputTransitionCheck = true;
				}
				if (!inputTransitionCheck) {
					std::cout << "There isn't such a state in the current automaton. Please enter another one: ";
					std::cin >> transitionTable[i][j];
				}
			}
		}
	}

	//въвеждане на начално състояние
	std::cout << "Please enter an entry state: ";
	std::cin >> entryState;
	bool stateFlag = false;
	while (!stateFlag) {
		for (int k = 0; k < statesCnt; k++) {
			if (strcmp(entryState.getStateName(), states[k].getStateName()) == 0) stateFlag = true;
		}
		if (!stateFlag) {
			std::cout << "You can't enter this entry state, because there isn't such a state in the current automaton. Please enter another one: ";
			std::cin >> entryState;
		}
	}

	//въвеждане на брой крайни състояния
	std::cout << "Please enter the number of final states: ";
	std::cin >> finalStatesCnt;

	//изтриване на стария масив с крайни състояния и създаване на нов
	if (finalStates != nullptr) {
		delete[] finalStates;
	}
	finalStates = new State[finalStatesCnt];

	//въвеждане на крайните състояния
	for (int i = 0; i < finalStatesCnt; i++) {
		std::cout << "Enter final state number [" << i+1 << "]: ";
		std::cin >> finalStates[i];
		stateFlag = false;
		while (!stateFlag) {
			for (int k = 0; k < statesCnt; k++) {
				if (strcmp(finalStates[i].getStateName(), states[k].getStateName()) == 0) stateFlag = true;
			}
			if (!stateFlag) {
				std::cout << "You can't enter this final state, because there isn't such a state in the current automaton. Please enter another one: ";
				std::cin >> finalStates[i];
			}
		}
	}

	return 0;
}
//-------------------Na dari potencilnite gluposti-------------------
//template <typename T>
//int fillDFAutomatonFile( ifstream& in);
template<typename T>
std::ifstream& DFAutomaton<T>::fillDFAutomaton(std::ifstream& in) {
	//br sustoqnia
    in >> statesCnt;
	//samite sustoqnie
	if (states != nullptr) {
		delete[]states;
	}
	states = new State[statesCnt];
	for (int i = 0; i < statesCnt; i++) {
		in >> states[i];
	}

	//number of alphabet symbols
	in >> alphabetSize;

	//adding el from the alphabet
	if (alphabet != nullptr) {
		delete[] alphabet;
	}
	alphabet = new T[alphabetSize];

	for (int i = 0; i < alphabetSize; i++) {
		in >> alphabet[i];
	}

	//deleting the old TT and intializing TT with  new data
	if (transitionTable != nullptr) {
		for (int i = 0; i < statesCnt; i++) {
			delete[] transitionTable[i];
		}
		delete[] transitionTable;
	}

	transitionTable = new State * [statesCnt];
	for (int i = 0; i < statesCnt; i++) {
		transitionTable[i] = new State[alphabetSize];
	}

	//TODO vuvejda se  transition table
	for (int i = 0; i < statesCnt; i++) {
		for (int j = 0; j < alphabetSize; j++) {
			in >> transitionTable[i][j];
			//TODO check the input
			bool inputTransitionCheck = false;
			while (!inputTransitionCheck) {
				for (int k = 0; k < statesCnt; k++) {
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
		for (int h = 0; h < statesCnt; h++) {
			if (strcmp(entryState.getStateName(), states[h].getStateName()) == 0) stateFlag = true;
		}
		if (!stateFlag) {
			//TODO: handle exception or don't
			std::cout << "Invalid entry state! Corrupted Automaton!";
			return in;
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
	for (int i = 0; i < finalStatesCnt; i++) {

		in >> finalStates[i];
		stateFlag = false;
		while (!stateFlag) {
			for (int h = 0; h < statesCnt; h++) {
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

//-------------------Krai na na dari potencilnite gluposti-------------------
//TODO Simo
//2filler
//2predefined functions
//TransitionTable
//2predefined functions

#endif
