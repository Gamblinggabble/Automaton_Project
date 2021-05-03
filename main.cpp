#include <iostream>
#include "AutomatonException.h"
#include "DeterminateFiniteAutomaton.h"
#include "State.h"

using namespace std;

int main() {

	//char arr[6] = { 'a', 'b', 'c', 'd', 'e' };
	int arr1[] = {9, 1, 2, 3, 4};
	DFAutomaton<int> autom1(5, arr1, 3, new State[3]{ State("q0"), State("q1"), State("q2") }, State("q0"), 1, new State[1]{ State("q2")});
	//DFAutomaton<int> autom = DFAutomaton<int>(5, arr1);

	//autom.printAlphabet(); cout << endl;
	autom1.printAlphabet(); cout << endl;

	//State s1;
	//State s2("green");
	//s1 = s2;

	return 0;
}