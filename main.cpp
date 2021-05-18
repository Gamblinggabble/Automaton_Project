#include <iostream>
#include "AutomatonException.h"
#include "DeterminateFiniteAutomaton.h"
#include "State.h"
#include "TransitionTable.h"
//#include <locale.h>
#include <cstdlib>

using namespace std;

int main() {

	char* arr = new char[6]{ 'a', 'b', 'c', 'd', 'e'};
	//cout << arr << endl;
	int arr1[] = {9, 1, 2, 3, 4};
	DFAutomaton<char> autom1(6, arr, 3, new State[3]{ State("q0"), State("q1"), State("q2") }, State("q0"), 1,  new State[1]{ State("q2")});
	DFAutomaton<int> autom;// = DFAutomaton<int>(5, arr1);

	/*autom1.printAlphabet(); cout << endl;
	cout << autom1.getEntryState().getStateName() << endl;
	autom1.setEntryState("gabii");
	cout << autom1.getEntryState().getStateName() << endl;*/

	State s1;
	State s2("green");
	s1 = s2;
	autom1.setEntryState(s1);
	cout << autom1.getEntryState().getStateName() << endl;
	
	/*ofstream of; of.open("file.out");
	if (!of) {
		cout << "Failed to open file.out" << endl;
		return 1;
	}
	of << autom1;*/

	cout << autom1 << endl;
	cout << autom << endl;


	return 0;
}