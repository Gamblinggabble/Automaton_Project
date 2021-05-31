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
		if (option > 11) {
			cout << "Choose between options from -1 to 11! Choose option: ";
			continue;
		}

		menu(option, automInt, automChar);
		

		cout << "Choose option: ";
	}

	return 0;
}