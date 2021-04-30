#include <iostream>
#include "AutomatonException.h"
#include "DeterminateFiniteAutomaton.h"
#include "State.h"

using namespace std;

int main() {

	char arr[6] = { 'a', 'b', 'c', 'd', 'e' };
	int arr1[] = {9, 1, 2, 3, 4};
	DeterminateFiniteAutomaton<int> autom1(5, arr1);
	DeterminateFiniteAutomaton<int> autom = DeterminateFiniteAutomaton<int>(5, arr1);


	autom.printAlphabet(); cout << endl;
	autom1.printAlphabet(); cout << endl;

	//State s1;
	//State s2("green");
	//s1 = s2;

	return 0;
}