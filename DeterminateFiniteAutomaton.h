#ifndef DF_AUTOMATON_H
#define DF_AUTOMATON_H

template <typename T>
class DeterminateFiniteAutomaton
{
public:
	DeterminateFiniteAutomaton(unsigned = 0, T* alphabet = nullptr);

	DeterminateFiniteAutomaton(const DeterminateFiniteAutomaton&);
	~DeterminateFiniteAutomaton();

	DeterminateFiniteAutomaton& operator=(const DeterminateFiniteAutomaton&);

	int printAlphabet();
private:
	T* alphabet;
	unsigned size;
};


#endif
