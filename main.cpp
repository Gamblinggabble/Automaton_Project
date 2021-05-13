#include <iostream>
#include <fstream>
#include "AutomatonException.h"
#include "DeterminateFiniteAutomaton.h"
#include "State.h"
#include "TransitionTable.h"

using namespace std;

int main() {

	//char arr[6] = { 'a', 'b', 'c', 'd', 'e' };
	int arr1[] = {9, 1, 2, 3, 4};
	//DFAutomaton<int> autom1(5, arr1, 3, new State[3]{ State("q0"), State("q1"), State("q2") }, State("q0"), 1,  new State[1]{ State("q2")});
	//DFAutomaton<int> autom = DFAutomaton<int>(5, arr1);

	//autom.printAlphabet(); cout << endl;
	//autom1.printAlphabet(); cout << endl;


	//DFAutomaton<int> autom2();
	//autom2.printAlphabet();

	//State s1;
	//State s2("green");
	//s1 = s2;

	//TransitionTable<int> tt1(autom1);
	//cout << tt1;
	

	return 0;
}