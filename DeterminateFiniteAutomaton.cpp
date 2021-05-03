#include"DeterminateFiniteAutomaton.h"
#include <iostream>
#include <cstring>

//DFAutomaton<char>::DFAutomaton(unsigned alphabetSize, char* alphabet, unsigned statesCnt, State* states, const State& entryState,
//	unsigned finalStatesCnt, State* finalStates)
//	:statesCnt(statesCnt), states(new State[statesCnt]), entryState(entryState), finalStatesCnt(finalStatesCnt),
//	finalStates(new State[finalStatesCnt])
//{
//	if (alphabet != nullptr) {
//		//size is number of elements, not counting '\0'
//		this->alphabetSize = alphabetSize;
//		this->alphabet = new char[alphabetSize + 1];
//		strcpy_s(this->alphabet, alphabetSize + 1, alphabet);
//	}
//	else {
//		std::cout << "No alphabet entered! Default alphabet set - {a,b}" << std::endl;
//		this->alphabetSize = 2;
//		this->alphabet = new char[this->alphabetSize + 1]{ 'a', 'b' };
//	}
//
//	if (states != nullptr) {
//		for (unsigned i = 0; i < this->statesCnt; i++)
//		{
//			this->states[i] = states[i];
//		}
//
//		if (finalStates != nullptr) {
//			for (unsigned j = 0; j < this->finalStatesCnt; j++)
//			{
//				this->finalStates[j] = finalStates[j];
//			}
//		}
//		else this->finalStates = nullptr;
//	}
//	else this->states = nullptr;
//
//}
//DFAutomaton<char>::DFAutomaton(const DFAutomaton<char>& rhs)
//	:statesCnt(rhs.statesCnt), states(new State[rhs.statesCnt]), entryState(rhs.entryState), finalStatesCnt(rhs.finalStatesCnt),
//	finalStates(new State[rhs.finalStatesCnt]) {
//	if (rhs.alphabet != nullptr) {
//		alphabetSize = rhs.alphabetSize;
//		alphabet = new char[alphabetSize + 1];
//		strcpy_s(alphabet, alphabetSize + 1, rhs.alphabet);
//	}
//	else {
//		alphabetSize = 0;
//		alphabet = nullptr;
//	}
//
//	if (rhs.states != nullptr) {
//		for (unsigned i = 0; i < this->statesCnt; i++)
//		{
//			this->states[i] = rhs.states[i];
//		}
//
//		if (rhs.finalStates != nullptr) {
//			for (unsigned j = 0; j < this->finalStatesCnt; j++)
//			{
//				this->finalStates[j] = rhs.finalStates[j];
//			}
//		}
//		else this->finalStates = nullptr;
//	}
//	else this->states = nullptr;
//}
//DFAutomaton<char>& DFAutomaton<char>::operator=(const DFAutomaton<char>& rhs) {
//	if (this != &rhs) {
//		if (rhs.alphabet != nullptr) {
//			alphabetSize = rhs.alphabetSize;
//			alphabet = new char[alphabetSize + 1];
//			strcpy_s(alphabet, alphabetSize + 1, rhs.alphabet);
//		}
//		if (rhs.states != nullptr) {
//			this->statesCnt = rhs.statesCnt;
//			for (unsigned i = 0; i < this->statesCnt; i++)
//			{
//				this->states[i] = rhs.states[i];
//			}
//
//			if (rhs.finalStates != nullptr) {
//				this->finalStatesCnt = rhs.finalStatesCnt;
//				for (unsigned i = 0; i < this->finalStatesCnt; i++)
//				{
//					this->finalStates[i] = rhs.finalStates[i];
//				}
//			}
//			else {
//				this->finalStatesCnt = 0;
//				this->finalStates = nullptr;
//			}
//		}
//		else {
//			this->statesCnt = 0;
//			this->states = nullptr;
//		}
//	}
//
//	return *this;
//}
