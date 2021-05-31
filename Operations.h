#pragma once

#include <iostream>
#include "AutomatonException.h"
#include "DeterminateFiniteAutomaton.h"
#include "State.h"
#include <cstdlib>
#include <fstream>
#include <exception>
#include <sstream>
#include <string>

template <typename T>
DFAutomaton<T> intersectionAutomaton(const DFAutomaton<T>& automA, const DFAutomaton<T>& automB) {
	//create a new automaton
	DFAutomaton<T> tmpAutom;

	//set size of the automaton
	int alphabetSize = automA.getAlphabetSize();
	if (isAlphabetEqual(automA, automB)) {
		tmpAutom.setAlphabetSize(alphabetSize);

		//creating a temporary array for the alphabet to set the alphabet of the temporary automaton
		T* tmpAlphabet = new T[alphabetSize];
		for (int i = 0; i < alphabetSize; i++) {
			tmpAlphabet[i] = automA.getAlphabet()[i];
		}
		tmpAutom.setAlphabet(tmpAlphabet);
	}
	else {
		std::cout << "Automatons do not have common alphabets.";
		return automA;
	}

	//set number of states
	unsigned numberOfStates = automA.getStatesCnt() * automB.getStatesCnt();
	tmpAutom.setStatesCnt(numberOfStates);
	//set states
	State* tmpStates = new State[numberOfStates];
	std::stringstream intersectionStateName;
	int stateIndex = 0;
	for (int a = 0; a < automA.getStatesCnt(); a++) {
		for (int b = 0; b < automB.getStatesCnt(); b++) {
			intersectionStateName.str("");
			intersectionStateName << "(" << automA.getStates()[a] << "," << automB.getStates()[b] << ")";
			const std::string strStateName = intersectionStateName.str();
			const unsigned charStateNameSize = strStateName.size();
			char* charStateName = new char[charStateNameSize+1];
			for (int i = 0; i < charStateNameSize; i++) {
				charStateName[i] = strStateName[i];
			}
			charStateName[charStateNameSize] = '\0';
			//strcpy_s(charStateName, charStateNameSize, strStateName.c_str());
			tmpStates[stateIndex++].setStateName(charStateName);
			delete[] charStateName;
		}
	}
	tmpAutom.setStates(tmpStates);

	//set transitionTable
	State** tmpTransitionTable = new State * [numberOfStates];
	for (int i = 0; i < numberOfStates; i++) {
		tmpTransitionTable[i] = new State[alphabetSize];
	}
	stateIndex = 0;
	for (int a = 0; a < automA.getStatesCnt(); a++) {
		for (int b = 0; b < automB.getStatesCnt(); b++) {
			for (int alphaIndex = 0; alphaIndex < alphabetSize; alphaIndex++) {
				intersectionStateName.str("");
				intersectionStateName << "(" << automA.getTransitionTable()[a][alphaIndex] << "," << automB.getTransitionTable()[b][alphaIndex] << ")";
				const std::string strStateName = intersectionStateName.str();
				tmpTransitionTable[stateIndex][alphaIndex] = strStateName.c_str();
			}
			stateIndex++;
		}
	}
	tmpAutom.setTransitionTable(tmpTransitionTable);

	//set the entry state
	intersectionStateName.str("");
	intersectionStateName << "(" << automA.getEntryState() << "," << automB.getEntryState() << ")";
	const std::string strEntryState = intersectionStateName.str();
	tmpAutom.setEntryState(State(strEntryState.c_str()));

	//set final states
	int tmpFinalStatesCnt = 0;
	State* tmpFinalStatesPre = new State[numberOfStates];
	for (int a = 0; a < automA.getStatesCnt(); a++) {
		for (int b = 0; b < automB.getStatesCnt(); b++) {
			bool isFinalA = false;
			bool isFinalB = false;

			for (int fa = 0; fa < automA.getFinalStatesCnt(); fa++) {
				if (automA.getStates()[a] == automA.getFinalStates()[fa]) {
					isFinalA = true;
					break;
				}
			}
			for (int fb = 0; fb < automB.getFinalStatesCnt(); fb++) {
				if (automB.getStates()[b] == automB.getFinalStates()[fb]) {
					isFinalB = true;
					break;
				}
			}

			if (isFinalA && isFinalB) {
				intersectionStateName.str("");
				intersectionStateName << "(" << automA.getStates()[a] << "," << automB.getStates()[b] << ")";
				const std::string strFinalStateName = intersectionStateName.str();

				tmpFinalStatesPre[tmpFinalStatesCnt] = State(strFinalStateName.c_str());
				tmpFinalStatesCnt++;
			}

		}
	}
	tmpAutom.setFinalStatesCnt(tmpFinalStatesCnt);

	State* tmpFinalStates = new State[tmpFinalStatesCnt];
	for (int i = 0; i < tmpFinalStatesCnt; i++) {
		tmpFinalStates[i] = tmpFinalStatesPre[i];
	}

	tmpAutom.setFinalStates(tmpFinalStates);
	return tmpAutom;
}
template <typename T>
DFAutomaton<T> unionAutomaton(const DFAutomaton<T>& automA, const DFAutomaton<T>& automB) {
	//create a new automaton
	DFAutomaton<T> tmpAutom;

	//set size of the automaton
	int alphabetSize = automA.getAlphabetSize();
	if (isAlphabetEqual(automA, automB)) {
		tmpAutom.setAlphabetSize(alphabetSize);

		//creating a temporary array for the alphabet to set the alphabet of the temporary automaton
		T* tmpAlphabet = new T[alphabetSize];
		for (int i = 0; i < alphabetSize; i++) {
			tmpAlphabet[i] = automA.getAlphabet()[i];
		}
		tmpAutom.setAlphabet(tmpAlphabet);
	}
	else {
		std::cout << "Automatons do not have common alphabets.";
		return automA;
	}

	//set number of states
	unsigned numberOfStates = automA.getStatesCnt() * automB.getStatesCnt();
	tmpAutom.setStatesCnt(numberOfStates);
	//set states
	State* tmpStates = new State[numberOfStates];
	std::stringstream intersectionStateName;
	int stateIndex = 0;
	for (int a = 0; a < automA.getStatesCnt(); a++) {
		for (int b = 0; b < automB.getStatesCnt(); b++) {
			intersectionStateName.str("");
			intersectionStateName << "(" << automA.getStates()[a] << "," << automB.getStates()[b] << ")";
			const std::string strStateName = intersectionStateName.str();
			const unsigned charStateNameSize = strStateName.size();
			char* charStateName = new char[charStateNameSize + 1];
			for (int i = 0; i < charStateNameSize; i++) {
				charStateName[i] = strStateName[i];
			}
			charStateName[charStateNameSize] = '\0';
			//strcpy_s(charStateName, charStateNameSize, strStateName.c_str());
			tmpStates[stateIndex++].setStateName(charStateName);
			delete[] charStateName;
		}
	}
	tmpAutom.setStates(tmpStates);

	//set transitionTable
	State** tmpTransitionTable = new State * [numberOfStates];
	for (int i = 0; i < numberOfStates; i++) {
		tmpTransitionTable[i] = new State[alphabetSize];
	}
	stateIndex = 0;
	for (int a = 0; a < automA.getStatesCnt(); a++) {
		for (int b = 0; b < automB.getStatesCnt(); b++) {
			for (int alphaIndex = 0; alphaIndex < alphabetSize; alphaIndex++) {
				intersectionStateName.str("");
				intersectionStateName << "(" << automA.getTransitionTable()[a][alphaIndex] << "," << automB.getTransitionTable()[b][alphaIndex] << ")";
				const std::string strStateName = intersectionStateName.str();
				tmpTransitionTable[stateIndex][alphaIndex] = strStateName.c_str();
			}
			stateIndex++;
		}
	}
	tmpAutom.setTransitionTable(tmpTransitionTable);

	//set the entry state
	intersectionStateName.str("");
	intersectionStateName << "(" << automA.getEntryState() << "," << automB.getEntryState() << ")";
	const std::string strEntryState = intersectionStateName.str();
	tmpAutom.setEntryState(State(strEntryState.c_str()));

	//set final states
	int tmpFinalStatesCnt = 0;
	State* tmpFinalStatesPre = new State[numberOfStates];
	for (int a = 0; a < automA.getStatesCnt(); a++) {
		for (int b = 0; b < automB.getStatesCnt(); b++) {
			bool isFinalA = false;
			bool isFinalB = false;

			for (int fa = 0; fa < automA.getFinalStatesCnt(); fa++) {
				if (automA.getStates()[a] == automA.getFinalStates()[fa]) {
					isFinalA = true;
					break;
				}
			}
			for (int fb = 0; fb < automB.getFinalStatesCnt(); fb++) {
				if (automB.getStates()[b] == automB.getFinalStates()[fb]) {
					isFinalB = true;
					break;
				}
			}

			if (isFinalA || isFinalB) {
				intersectionStateName.str("");
				intersectionStateName << "(" << automA.getStates()[a] << "," << automB.getStates()[b] << ")";
				const std::string strFinalStateName = intersectionStateName.str();

				tmpFinalStatesPre[tmpFinalStatesCnt] = State(strFinalStateName.c_str());
				tmpFinalStatesCnt++;
			}
		}
	}
	tmpAutom.setFinalStatesCnt(tmpFinalStatesCnt);

	State* tmpFinalStates = new State[tmpFinalStatesCnt];
	for (int i = 0; i < tmpFinalStatesCnt; i++) {
		tmpFinalStates[i] = tmpFinalStatesPre[i];
	}

	tmpAutom.setFinalStates(tmpFinalStates);
	return tmpAutom;
}
template <typename T>
DFAutomaton<T> complementAutomaton(DFAutomaton<T>& complement,const DFAutomaton<T>& automA) {

	DFAutomaton<T> tmpAutom;
	
	tmpAutom.setAlphabetSize(automA.getAlphabetSize());
	tmpAutom.setAlphabet(automA.getAlphabet());
	tmpAutom.setStatesCnt(automA.getStatesCnt());
	tmpAutom.setStates(automA.getStates());
	tmpAutom.setEntryState(automA.getEntryState());
	tmpAutom.setFinalStatesCnt(automA.getStatesCnt() - automA.getFinalStatesCnt());

	State* tmpFinalStates = new State[tmpAutom.getFinalStatesCnt()];
	unsigned cnt=0;
	for (unsigned i = 0; i < automA.getStatesCnt(); i++) {
		bool wasFinal = false;
		for (unsigned j = 0; j < automA.getFinalStatesCnt(); j++)
		{
			if (automA.getStates()[i]==automA.getFinalStates()[j]) {
				wasFinal = true;
				break;
			}
		}
		if (!wasFinal) {
			tmpFinalStates[cnt] = automA.getStates()[i];
			cnt++;
		}
	}
	tmpAutom.setFinalStates(tmpFinalStates);
	tmpAutom.setTransitionTable(automA.getTransitionTable());

	complement = tmpAutom;
	return tmpAutom;
}

template<typename T>
DFAutomaton<T> operator&(const DFAutomaton<T>& automA, const DFAutomaton<T>& automB) {
	return intersectionAutomaton(automA, automB);
}

template<typename T>
DFAutomaton<T> operator|(const DFAutomaton<T>& automA, const DFAutomaton<T>& automB) {
	return unionAutomaton(automA, automB);
}

template<typename T>
DFAutomaton<T> operator^(DFAutomaton<T>& complement,const DFAutomaton<T>& automA) {
	return complementAutomaton(complement,automA);
}


template<typename T>
bool isAlphabetEqual(const DFAutomaton<T>& automA, const DFAutomaton<T>& automB) {
	//function to tell if alphabets of two automatons are equal

	if (automA.getAlphabetSize() == automB.getAlphabetSize()) {
		bool isThere;
		int alphabetSize = automA.getAlphabetSize();
		for (int i = 0; i < alphabetSize; i++) {
			isThere = false;
			for (int j = 0; j < alphabetSize; j++) {
				//if (typeid(T) == typeid(char)) {
				//	if (strcmp((char*)automA.getAlphabet()[i], (char*)automB.getAlphabet()[j]) == 0) isThere = true;
				//}
				//else if (typeid(T) == typeid(int)) {
				if (automA.getAlphabet()[i] == automB.getAlphabet()[j]) {
					isThere = true;
					break;
				}
				//}
			}
			if (!isThere) throw "isAlphabetFunction operates with automatons, whose alphabet consists of integers or chars only!";
		}
		return true;
	}
	else return false;
}

