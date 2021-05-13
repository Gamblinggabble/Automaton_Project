//#ifndef TRANSITION_TABLE_H
//#define TRANSITION_TABLE_H
//
//#include <iostream>
//#include <sstream>
//#include "DeterminateFiniteAutomaton.h"
//
//
//template <typename T>
//class TransitionTable
//{
//public:
//	//TODO: Simo - BIGFIVE
//	TransitionTable(DFAutomaton<T>);
//	~TransitionTable();
//	State** getTranstionTable() const;
//	unsigned getRowSize() const;
//	unsigned getColSize() const;
//	
//	std::ostream& ins(std::ostream&);
//	int fillTransitionTable(std::istream&);
//private:
//	State** transitionTable;
//	unsigned rowSize;
//	unsigned colSize;
//	State* states;
//	T* alphabet;
//};
//
//
//template <typename T>
//TransitionTable<T>::TransitionTable(DFAutomaton<T> automaton)
//{
//	rowSize = automaton.getStatesCnt();
//	colSize = automaton.getAlphabetSize();
//
//	transitionTable = new State * [rowSize];
//	for (int i = 0; i < rowSize; i++) {
//		transitionTable[i] = new State[colSize];
//	}
//	states = new State[automaton.getStatesCnt()];
//	for (int i = 0; i < automaton.getStatesCnt(); i++) {
//		states[i] = automaton.getStates()[i];
//	}
//	alphabet = new T[automaton.getAlphabetSize()];
//	for (int i = 0; i < automaton.getAlphabetSize(); i++) {
//		alphabet[i] = automaton.getAlphabet()[i];
//	}
//	 
//}
//
//template <typename T>
//TransitionTable<T>::~TransitionTable()
//{
//	for (int i = 0; i < rowSize; i++) {
//		delete[] transitionTable[i];
//	}
//	delete[] transitionTable;
//
//	if (states != nullptr) {
//		delete[] states;
//	}
//	if (alphabet != nullptr) {
//		delete[] alphabet;
//	}
//}
//
//template <typename T>
//State** TransitionTable<T>::getTranstionTable() const {
//	return transitionTable;
//}
//
//template <typename T>
//unsigned TransitionTable<T>::getRowSize() const {
//	return rowSize;
//}
//
//template <typename T>
//unsigned TransitionTable<T>::getColSize() const {
//	return colSize;
//}
//
//template <typename T>
//std::ostream& TransitionTable<T>::ins(std::ostream& out) {
//	for (int i = 0; i < rowSize; i++) {
//		for (int j = 0; j < colSize; j++) {
//			out << transitionTable[i][j] << "\t";
//		}
//		out << std::endl;
//	}
//	return out;
//}
//
//template <typename T>
//std::ostream& operator<<(std::ostream& out, TransitionTable<T>& rhs) {
//	return rhs.ins(out);
//}
//
////TODO: Simo - enter table with predefined >>
////cout << "Enter q[" << i << "], " << alphabet(j) << ": ";
////cin >> transitionTable[i][j];
//
//template<typename T>
//int TransitionTable<T>::fillTransitionTable(std::istream& in) {
//	
//	switch (typeid(T)) {
//	case(typeid(int)): 
//		for (int i = 0; i < rowSize; i++) {
//			for (int j = 0; j < colSize; j++) {
//				std::cout << "Please enter (" << states[i] << "," << alphabet[j] << "): ";
//				std::cin >> transitionTable[i][j];
//				//TODO проверка на входа
//			}
//		}
//		break;
//	case(typeid(char*)):
//		break;
//	default: 
//		break;
//	}
//
//	return 0;
//}
////int TransitionTable<T>::fillTransitionTable(std::ifstream& in) {
////
////	switch (typeid(T)) {
////	case(typeid(int)):
////		for (int i = 0; i < rowSize; i++) {
////			for (int j = 0; j < colSize; j++) {
////				in >>
////			}
////		}
////		break;
////	case(typeid(char*)):
////		break;
////	default:
////		break;
////	}
////
////	return 0;
////}
//
//#endif