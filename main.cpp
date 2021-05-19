#include <iostream>
#include <fstream>
#include "AutomatonException.h"
#include "DeterminateFiniteAutomaton.h"
#include "State.h"
#include "TransitionTable.h"

using namespace std;

int main() {


	ifstream input_file;
	input_file.open("file.in");

	if (!input_file) {
		 //check if it is open correctly
		cerr << "Could not open file file.n" << endl;
		return 1;
	}
	
	DFAutomaton <int> autom3;
	input_file >> autom3;
	cout << autom3.getEntryState();

	input_file.close();

	return 0;
}