
#include <iostream>
#include "AutomatonException.h"
#include "DeterminateFiniteAutomaton.h"
#include "State.h"
#include <cstdlib>
#include <fstream>
#include "Operations.h"

using namespace std;

int main() {

	//ifstream input_file;
	//input_file.open("file.in");

	//if (!input_file) {
	//	 //check if it is open correctly
	//	cerr << "Could not open file file.n" << endl;
	//	return 1;
	//}

	//DFAutomaton <int> autom3;
	//input_file >> autom3;
	//input_file.close();

	//cout << autom3;

	//cout << boolalpha << autom3("001");

	//char* arr = new char[6]{ 'a', 'b', 'c', 'd', 'e'};
	////cout << arr << endl;
	//int arr1[] = {9, 1, 2, 3, 4};
	//DFAutomaton<char> autom1(6, arr, 3, new State[3]{ State("q0"), State("q1"), State("q2") }, nullptr, State("q0"), 1,  new State[1]{ State("q2")});
	//DFAutomaton<int> autom;// = DFAutomaton<int>(5, arr1);

	///*autom1.printAlphabet(); cout << endl;
	//cout << autom1.getEntryState().getStateName() << endl;
	//autom1.setEntryState("gabii");
	//cout << autom1.getEntryState().getStateName() << endl;*/

	//State s1;
	//cin >> s1;
	//cout << s1 << endl;
	//State s2("green");
	//s1 = s2;
	//autom1.setEntryState(s1);
	////cout << autom1.getEntryState().getStateName() << endl;
	//
	//ofstream of;
	//of.open("file.out");
	//if (!of) {
	//	cout << "Failed to open file.out" << endl;
	//	return 1;
	//}

	//DFAutomaton<int> autom2;
	//cin >> autom2;
	//cout << endl;
	//cout << autom2;
	//of << autom2;

	//of.close();

	//

	DFAutomaton<char> autom4;
	ifstream input_file_A;
	input_file_A.open("automA.txt");

	if (!input_file_A) {
		//check if it is open correctly
		cerr << "Could not open file file.n" << endl;
		return 1;
	}
	input_file_A >> autom4;

	input_file_A.close();



	DFAutomaton<char> autom5;
	ifstream input_file_B;
	input_file_B.open("automB.txt");

	if (!input_file_B) {
		//check if it is open correctly
		cerr << "Could not open file file.n" << endl;
		return 1;
	}
	input_file_B >> autom5;

	input_file_B.close();

	cout << endl;
	//cout << boolalpha << isAlphabetEqual(autom4, autom5) << noboolalpha << endl;
	DFAutomaton<char> automProduct =  autom4&autom5;
	cout << boolalpha << automProduct("2122");

	return 0;
}