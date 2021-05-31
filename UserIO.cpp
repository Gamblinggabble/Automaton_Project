#include "UserIO.h"
#include "State.h"


const unsigned FILE_NAME_MAX_LEN = 50;
const unsigned WORD_MAX_LEN = 50;
bool workingWithIntAutom = true;

int printMenu() {

	std::cout << std::string(100, '*') << std::endl;
	std::cout << std::string(48, ' ') << "MENU" << std::string(48, ' ') << std::endl << std::endl;
	std::cout << "-1 - clear console" << std::endl;
	std::cout << "0 - exit program" << std::endl;
	std::cout << "1 - create an automat from console" << std::endl;
	std::cout << "2 - create an automat from a file" << std::endl;
	std::cout << "3 - print entry state" << std::endl;
	std::cout << "4 - change entry state" << std::endl;
	std::cout << "5 - print final states " << std::endl;
	std::cout << "6 - print transition table" << std::endl;
	std::cout << "7 - print automat on console" << std::endl;
	std::cout << "8 - save automat in a file" << std::endl;
	std::cout << "9 - view SVG of automat" << std::endl;
	std::cout << "10 - read word" << std::endl; // checks if word exists in the language of the automaton
	std::cout << "11 - print menu" << std::endl;
	std::cout << std::string(100, '*') << std::endl;

	return 0;
}

int menu(int option, DFAutomaton<int>& automInt, DFAutomaton<char>& automChar) {

	switch (option)
	{
	case -1:
		clearConsole();
		break;
	case 1:
		createAutomatConsole(automInt, automChar);
		break;
	case 2:
		createAutomatFile(automInt, automChar);
		break;
	case 3:
		printEntryState(automInt, automChar);
		break;
	case 4:
		changeEntryState(automInt, automChar);
		break;
	case 5:
		printFinalStates(automInt, automChar);
		break;
	case 6:
		printTransitionTable(automInt, automChar);
		break;
	case 7:
		printAutomatOnConsole(automInt, automChar);
		break;
	case 8:
		printAutomatInFile(automInt, automChar);
		break;
	case 9:
		loadSVG(automInt, automChar);
		break;
	case 10:
		readWord(automInt, automChar);
		break;
	case 11:
		printMenu();
		break;
	default:
		break;
	}
	return 0;
}

int clearConsole() {

	system("CLS");
	printMenu();
	return 0;
}

int createAutomatConsole(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar) {
	/*Въвеждане на тип на азбуката в автомата (1 - цяло число, 2 – символен тип): 1*/
	cout << "Please enter type of automaton (1 - working with int alphabet, 2 - working with char alphabet): ";
	int f;
	std::cin >> f;
	if (f == 1) {
		workingWithIntAutom = true;
		cin >> automInt;
	}
	else if (f == 2) {
		workingWithIntAutom = false;
		cin >> automChar;
	}

	return 0;
}
int createAutomatFile(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar) {

	char filename[FILE_NAME_MAX_LEN];
	cout << "Please enter name of file to read from: ";
	cin >> filename;
	std::ifstream fin(filename);
	int f;
	fin >> f;
	if (f == 1) {
		workingWithIntAutom = true;
		fin >> automInt;
	}
	else if (f == 2) {
		workingWithIntAutom = false;
		fin >> automChar;
	}
	fin.close();
	return 0;
}

int printEntryState(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar) {

	std::cout << "Entry state - ";
	if (workingWithIntAutom)
		std::cout << automInt.getEntryState() << std::endl;
	else
		std::cout << automChar.getEntryState() << std::endl;

	return 0;
}
int changeEntryState(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar) {

	cout << "Enter the name of the new entry state: ";
	char newStateName[MAX_NAME_LENGHT];
	cin >> newStateName;

	if (workingWithIntAutom)
		automInt.setEntryState(newStateName);
	else
		automChar.setEntryState(newStateName);
	return 0;
}

int printFinalStates(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar) {

	unsigned sz;
	if (workingWithIntAutom) {
		sz = automInt.getFinalStatesCnt();
		std::cout << "Final state" << (sz == 1 ? "" : "s") << ": ";

		for (unsigned i = 0; i < sz; i++)
		{
			std::cout << automInt.getFinalStates()[i];
			if (i != sz - 1) std::cout << ", ";
		}
	}
	else {
		sz = automChar.getFinalStatesCnt();
		std::cout << "Final state" << (sz == 1 ? "" : "s") << ": ";

		for (unsigned i = 0; i < sz; i++)
		{
			std::cout << automChar.getFinalStates()[i];
			if (i != sz - 1) std::cout << ", ";
		}
	}

	if (sz == 0) cout << "none";
	std::cout << std::endl;
	return 0;
}
int printTransitionTable(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar) {

	if (workingWithIntAutom)
		automInt.printTransitionTable(std::cout);
	else
		automChar.printTransitionTable(std::cout);
	return 0;
}

int printAutomatOnConsole(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar) {

	std::cout << std::endl;

	if (workingWithIntAutom)
		cout << automInt;
	else
		cout << automChar;

	std::cout << std::endl;
	return 0;
}
int printAutomatInFile(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar) {

	char filename[FILE_NAME_MAX_LEN];
	cout << "Please enter name of file to write in: ";
	cin >> filename;
	std::ofstream fout(filename);
	
	if (workingWithIntAutom) {
		fout << automInt;
	}
	else {
		fout << automInt;
	}
	fout.close();

	return 0;
}

int readWord(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar) {

	std::cout << "Please enter word: ";
	char word[WORD_MAX_LEN];
	std::cin.getline(word, WORD_MAX_LEN); //TODO: beware of getline
	std::cin >> word;
	bool read;
	if (workingWithIntAutom) {
		read = automInt(word);
	}
	else {
		read = automChar(word);
	}

	if (read) {
		std::cout << "The word EXISTS in the language of the automaton! :)";
	}
	else {
		std::cout << "The word DOES NOT EXIST in the language of the automaton! :(";
	}
	std::cout << std::endl;

	return 0;
}

int loadSVG(DFAutomaton<int>& automInt, DFAutomaton<char>& automChar) {

	//std::ofstream fout("../demoSVG/demo.svg");
	//if (!fout) {
	//	std::cerr << "File demo.svg could not be opened!" << std::endl;
	//	return 1;
	//}
	//fout << "<svg width=\"800\" height=\"100\" xmlns=\"http://www.w3.org/2000/svg\"><circle cx = \"50\" cy = \"50\" r = \"40\" / >";
	//fout << "<defs>	<marker id = \"arrowhead\" markerWidth = \"10\" markerHeight = \"7\" refX = \"0\" refY = \"3.5\" orient = \"auto\">";
	//fout << "<polygon points = \"0 0, 10 3.5, 0 7\" / >	< / marker>	< / defs> <line x1 = \"100\" y1 = \"50\" x2 = \"150\" y2 = \"50\" stroke - width = \"3\" stroke = \"black\" marker - end = \"url(#arrowhead)\" / >";
	//fout << "<circle class = \"final\" cx = \"230\" cy = \"50\" r = \"40\" / >	< / svg>";
	//fout.close();

	std::stringstream linker;
	linker << "MicrosoftEdge http://magjac.com/graphviz-visual-editor/?dot=strict%20digraph{%0Arankdir=LR;%0A";

	if (workingWithIntAutom)
		linker << automInt.produceSvg();
	else
		linker << automChar.produceSvg();

	system(linker.str().c_str());
	/*	b[shape = "polygon" style = "filled" fillcolor = "pink"]
		c[]
		a->b
		b->a
		a->c
		b->b
	});*/
	return 0;
}