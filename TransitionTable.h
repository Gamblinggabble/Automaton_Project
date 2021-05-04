#ifndef TRANSITION_TABLE_H
#define TRANSITION_TABLE_H

#include <iostream>
#include "DeterminateFiniteAutomaton.h"


template <typename T>
class TransitionTable
{
public:
	//TODO: Simo - BIGFIVE
	TransitionTable(DFAutomaton<T>);
	~TransitionTable();
	State** getTranstionTable() const;
	unsigned getRowSize() const;
	unsigned getColSize() const;
	
	std::ostream& ins(std::ostream&);
private:
	State** transitionTable;
	unsigned rowSize;
	unsigned colSize;
};


template <typename T>
TransitionTable<T>::TransitionTable(DFAutomaton<T> automaton)
{
	rowSize = automaton.getStatesCnt();
	colSize = automaton.getAlphabetSize();

	transitionTable = new State * [rowSize];
	for (int i = 0; i < rowSize; i++) {
		transitionTable[i] = new State[colSize];
	}
}

template <typename T>
TransitionTable<T>::~TransitionTable()
{
	for (int i = 0; i < rowSize; i++) {
		delete[] transitionTable[i];
	}
	delete[] transitionTable;
}

template <typename T>
State** TransitionTable<T>::getTranstionTable() const {
	return transitionTable;
}

template <typename T>
unsigned TransitionTable<T>::getRowSize() const {
	return rowSize;
}

template <typename T>
unsigned TransitionTable<T>::getColSize() const {
	return colSize;
}

template <typename T>
std::ostream& TransitionTable<T>::ins(std::ostream& out) {
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < colSize; j++) {
			out << transitionTable[i][j] << "\t";
		}
		out << std::endl;
	}
	return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, TransitionTable<T>& rhs) {
	return rhs.ins(out);
}

//TODO: Simo - enter table with predefined >>
//cout << "Enter q[" << i << "], " << alphabet(j) << ": ";
//cin >> transitionTable[i][j];


#endif