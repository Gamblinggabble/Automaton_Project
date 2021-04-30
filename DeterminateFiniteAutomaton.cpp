#include"DeterminateFiniteAutomaton.h"
#include <iostream>
#include <cstring>

DeterminateFiniteAutomaton<char>::DeterminateFiniteAutomaton(unsigned size, char* alphabet) {
	if (alphabet != nullptr) {
		//size is number of elements, not counting '\0'
		this->size = size;
		this->alphabet = new char[size + 1];
		strcpy_s(this->alphabet, size + 1, alphabet);
	}
	else {
		std::cout << "No alphabet entered! Default alphabet set - {a,b}" << std::endl;
		this->size = 2;
		this->alphabet = new char[this->size + 1]{ 'a', 'b' };
	}
}
DeterminateFiniteAutomaton<int>::DeterminateFiniteAutomaton(unsigned size, int* alp) {
	if (alp != nullptr) {
		this->size = size;
		this->alphabet = new int[size];
		for (unsigned i = 0; i < size; i++)
		{
			this->alphabet[i] = alp[i];
		}
	}
	else {
		std::cout << "No alphabet entered! Default alphabet set - {0,1}" << std::endl;
		this->size = 2;
		this->alphabet = new int[2]{ 0, 1 };
	}
}


DeterminateFiniteAutomaton<char>::DeterminateFiniteAutomaton(const DeterminateFiniteAutomaton<char>& rhs) {
	if (rhs.alphabet != nullptr) {
		size = rhs.size;
		alphabet = new char[size + 1];
		strcpy_s(alphabet, size + 1, rhs.alphabet);
	}
	else {
		size = 0;
		alphabet = nullptr;
	}
}
DeterminateFiniteAutomaton<int>::DeterminateFiniteAutomaton(const DeterminateFiniteAutomaton<int>& rhs) {
	if (rhs.alphabet != nullptr) {
		size = rhs.size;
		alphabet = new int[size];
		for (unsigned i = 0; i < size; i++)
		{
			alphabet[i] = rhs.alphabet[i];
		}
	}
	else {
		size = 0;
		alphabet = nullptr;
	}
}

DeterminateFiniteAutomaton<char>::~DeterminateFiniteAutomaton() {
	if (alphabet != nullptr) {
		delete[] alphabet;
	}
}
DeterminateFiniteAutomaton<int>::~DeterminateFiniteAutomaton() {
	if (alphabet != nullptr) {
		delete[] alphabet;
	}
}

DeterminateFiniteAutomaton<char>& DeterminateFiniteAutomaton<char>::operator=(const DeterminateFiniteAutomaton<char>& rhs) {
	if (this != &rhs) {
		if (rhs.alphabet != nullptr) {
			size = rhs.size;
			alphabet = new char[size + 1];
			strcpy_s(alphabet, size + 1, rhs.alphabet);
		}
	}

	return *this;
}
DeterminateFiniteAutomaton<int>& DeterminateFiniteAutomaton<int>::operator=(const DeterminateFiniteAutomaton<int>& rhs) {
	if (this != &rhs) {
		if (rhs.alphabet != nullptr) {
			size = rhs.size;
			alphabet = new int[size];
			for (unsigned i = 0; i < size; i++)
			{
				alphabet[i] = rhs.alphabet[i];
			}
		}
	}

	return *this;
}

int DeterminateFiniteAutomaton<char>::printAlphabet() {
	for (unsigned i = 0; i < size; i++)
	{
		std::cout << alphabet[i] << " ";
	}
	return 0;
}
int DeterminateFiniteAutomaton<int>::printAlphabet() {
	for (unsigned i = 0; i < size; i++)
	{
		std::cout << alphabet[i] << " ";
	}
	return 0;
}