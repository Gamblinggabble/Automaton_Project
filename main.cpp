#include <iostream>
#include "AutomatonException.h"
#include "DeterminateFiniteAutomaton.h"
#include "State.h"
#include <cstdlib>
#include <fstream>
#include "Operations.h"
#include "UserIO.h"

using namespace std;

int main() {

	DFAutomaton<int> automInt;
	DFAutomaton<char> automChar;

	printMenu();

	cout << "Choose option: ";
	int option;
	while (cin >> option) {
		if (option == 0) break;
		if (option > 14) {
			cout << "Choose between options from -1 to 14! Choose option: ";
			continue;
		}
		if ((option >= 12 && option <= 14) && (automInt.getTransitionTable() == nullptr && automChar.getTransitionTable() == nullptr)) {
			cout << std::endl << "You must first create an automaton using option 1 or 2!" << std::endl;
			cout << "Choose option: ";
			continue;
		}

		menu(option, automInt, automChar);
		

		cout << "Choose option: ";
	}

	return 0;
}