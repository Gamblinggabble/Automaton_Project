#ifndef DF_AUTOMATON_H
#define DF_AUTOMATON_H

#include "State.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip> 


template <typename T>
class DFAutomaton
{
public:
	DFAutomaton(unsigned alphabetSize = 0, T* alphabet = nullptr, unsigned statesCnt = 0, State* states = nullptr, State** transitionTable = nullptr,
		const State& entryState = State("NoName"), unsigned finalStatesCnt = 0, State* finalStates = nullptr);

	template <typename T> friend  std::istream& operator>>(std::istream&, DFAutomaton<T>&);

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

	int printAlphabet() const; //TODO: help func, could be deleted
	void printTransitionTable(std::ostream& out) const;
	void printTransitionTable(std::ofstream& out) const;
	std::ostream& ins(std::ostream&) const;
	std::ofstream& ins(std::ofstream&) const;
	std::istream& fillDFAutomaton(std::istream&);
private:
	T* alphabet;
	//number of elements in the alphabet
	//DISCLAMER! if T is of type char, \0 is not counted in alphabetSize
	unsigned alphabetSize;

	unsigned statesCnt;
	State* states;
	State** transitionTable;
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
std::istream& operator>>(std::istream& in, DFAutomaton<T>& rhs) {
	return rhs.fillDFAutomaton(in);
}

//template <typename T>
//std::ifstream& operator>>(std::ifstream& in, DFAutomaton<T>& rhs) {
//	rhs.fillDFAutomatonFile(in);
//	return in;
//}

template <typename T>
DFAutomaton<T>::DFAutomaton(unsigned alphabetSize, T* alphabet, unsigned statesCnt, State* states, State** transitionTable,
	const State& entryState, unsigned finalStatesCnt, State* finalStates)
	:statesCnt(statesCnt), /*states(new State[statesCnt]),*/ entryState(entryState), finalStatesCnt(finalStatesCnt),
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
		//added
		if (this->states != nullptr) {
			delete[]this->states;
		}
		this->states = new State[statesCnt];

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


	//�������� �� transition table
	if (transitionTable != nullptr) {
		//�����������
		this->transitionTable = new State * [this->statesCnt];
		for (int i = 0; i < this->statesCnt; i++) {
			this->transitionTable[i] = new State[this->alphabetSize];
		}
		//��������������/ �������� �� ����������
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

	//�������� �� transition table
	//��������� ���� �� ��������� �� ������� ������ ���, ������ ����� ������������� ���� ��������
	if (rhs.transitionTable != nullptr) {
		//����� ������� �������
		for (int i = 0; i < statesCnt; i++) {
			delete[] transitionTable[i];
		}
		delete[] transitionTable;

		//��������� ����
		transitionTable = new State * [statesCnt];
		for (int i = 0; i < statesCnt; i++) {
			transitionTable[i] = new State[alphabetSize];
		}

		//�������� ���������� �� ��������� �� ������ ������� � ��������� �� ������
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

	//��������� transition table
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

		//�������� �� transition table
		if (rhs.transitionTable != nullptr) {
			//����� ������� �������
			for (int i = 0; i < statesCnt; i++) {
				delete[] transitionTable[i];
			}
			delete[] transitionTable;

			//��������� ����
			transitionTable = new State * [statesCnt];
			for (int i = 0; i < statesCnt; i++) {
				transitionTable[i] = new State[alphabetSize];
			}

			//�������� ���������� �� ��������� �� ������ ������� � ��������� �� ������
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
int DFAutomaton<T>::printAlphabet() const {
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
void DFAutomaton<T>::printTransitionTable(std::ostream& out) const
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

		out << "Transition table: " << std::endl;
		cout << std::setw(SETW_PARAM); cout << "\t";
		for (unsigned i = 0; i < alphabetSize; i++)
		{
			cout << std::setw(SETW_PARAM) << alphabet[i];
		}
		cout << std::endl << std::endl;
		for (unsigned i = 0; i < statesCnt; i++)
		{
			cout << std::setw(SETW_PARAM) << states[i];
			cout << '\t';
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
}
template<typename T>
void DFAutomaton<T>::printTransitionTable(std::ofstream& out) const {

	if (transitionTable != nullptr) {
		//finds the longest state name
		unsigned SETW_PARAM = strlen(states[0].getStateName());
		for (unsigned i = 0; i < statesCnt; i++)
		{
			if (SETW_PARAM < strlen(states[i].getStateName()))
				SETW_PARAM = strlen(states[i].getStateName());
		}
		SETW_PARAM += 2;

		out << "Transition table: " << std::endl;
		out << std::setw(SETW_PARAM); out << "\t";
		for (unsigned i = 0; i < alphabetSize; i++)
		{
			out << std::setw(SETW_PARAM) << alphabet[i];
		}
		out << std::endl << std::endl;
		for (unsigned i = 0; i < statesCnt; i++)
		{
			out << std::setw(SETW_PARAM) << states[i];
			out << '\t';
			for (unsigned j = 0; j < alphabetSize; j++)
			{
				out << std::setw(SETW_PARAM) << transitionTable[i][j];
			}
			out << std::endl;
		}
	}
	else {
		out << "Transition table: not entered" << std::endl;
	}
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

	out << "Entry state: " << entryState.getStateName() << std::endl;
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

	fout << "Alphabet: ";
	for (unsigned i = 0; i < alphabetSize; i++)
	{
		fout << alphabet[i] << " ";
	}
	fout << std::endl;
	printTransitionTable(fout);
	fout << "Entry state: " << entryState.getStateName() << std::endl;
	fout << "Final state" << (finalStatesCnt > 1 ? "s" : "") << ": ";
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

template<typename T>
State* DFAutomaton<T>::getStates() const {
	return states;
}

template<typename T>
T* DFAutomaton<T>::getAlphabet() const {
	return alphabet;
}

template<typename T>
std::istream& DFAutomaton<T>::fillDFAutomaton(std::istream& in) {
	//number of states
	std::cout << "Please enter number of states: ";
	in >> statesCnt;

	//states
	if (states != nullptr) {
		delete[] states;
	}
	states = new State[statesCnt];
	for (int i = 0; i < statesCnt; i++) {
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
	alphabet = new T[alphabetSize];

	for (int i = 0; i < alphabetSize; i++) {
		std::cout << "Please enter symbol number [" << i + 1 << "]: ";
		in >> alphabet[i];
	}
	
	//TODO: make it a separate setTransitionTable function
	//delete current transition table and initialize a new one with entered size values
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

	//enter transition table
	for (int i = 0; i < statesCnt; i++) {
		for (int j = 0; j < alphabetSize; j++) {
			std::cout << "Please enter (" << states[i] << "," << alphabet[j] << "): ";
			in >> transitionTable[i][j];
			//check the input
			bool inputTransitionCheck = false;
			while (!inputTransitionCheck) {
				for (int k = 0; k < statesCnt; k++) {
					if (strcmp(states[k].getStateName(), transitionTable[i][j].getStateName()) == 0) {
						inputTransitionCheck = true;
						break;
					}
				}
				if (!inputTransitionCheck) {
					std::cout << "There isn't such a state in the current automaton. Please enter another one: ";
					in >> transitionTable[i][j];
				}
			}
		}
	}
	//enter entry state
	std::cout << "Please enter an entry state: ";
	in >> entryState;
	bool stateFlag = false;
	while (!stateFlag) {
		for (int k = 0; k < statesCnt; k++) {
			if (strcmp(entryState.getStateName(), states[k].getStateName()) == 0) {
				stateFlag = true;
				break;
			}
		}
		if (!stateFlag) {
			std::cout << "You can't enter this entry state, because there isn't such a state in the current automaton. Please enter another one: ";
			in >> entryState;
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
	for (int i = 0; i < finalStatesCnt; i++) {
		std::cout << "Enter final state number [" << i + 1 << "]: ";
		in >> finalStates[i];
		stateFlag = false;
		while (!stateFlag) {
			for (int k = 0; k < statesCnt; k++) {
				if (strcmp(finalStates[i].getStateName(), states[k].getStateName()) == 0) {
					stateFlag = true;
					break;
				}
			}
			if (!stateFlag) {
				std::cout << "You can't enter this final state, because there isn't such a state in the current automaton. Please enter another one: ";
				in >> finalStates[i];
			}
		}
	}

	return in;
}
#endif
