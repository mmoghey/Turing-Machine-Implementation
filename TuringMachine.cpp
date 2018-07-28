#include <fstream>
#include <iostream>
#include <string>
#include "TuringMachine.h"



using namespace std;
TuringMachine::TuringMachine()
{
}


TuringMachine::~TuringMachine()
{
}

void TuringMachine::readTransitionFile() {

int numStates;
char prevState, nextState, symbolIn, symbolOut;
char dir;
char ch;

int i, pos = 0;


ifstream fin("TuringMachineTransitionTable.txt");

// read the number of states
fin >> numStates;

for (i = 0; i < numStates; i++) { // store the states
	fin >> m_states[i];
}

fin >> m_startState;

//read the number of alphabets
fin >> m_numAlphabets;
for (i = 0; i < m_numAlphabets; i++) { // store the alphabets 
	fin >> m_alphabet[i];
}

//read the number of tape alphabets
fin >> m_numTapeAlphabets;
for (i = 0; i < m_numTapeAlphabets; i++) { // store the tape alphabets
	fin >> m_tapeAlphabet[i];
}

//start reading transitions
while (!fin.eof()) {
	fin >> prevState >> symbolIn >> nextState >> symbolOut >> dir;

	if (prevState < m_states[0] && prevState > m_states[numStates - 1]) {
		cout << "\n Invalid State ! \n";
		cin >> ch;
		exit(-1);
	}


	bool validIn = false;
	bool validOut = false;
	for (i = 0; i < m_numTapeAlphabets; i++) {
		if (m_tapeAlphabet[i] == symbolIn) {
			validIn = true;
		}
		if (m_tapeAlphabet[i] == symbolOut) {
			validOut = true;
		}
	}

	if ((validIn && validOut) == false) {
		cout << "\n Invalid symbol \n";
		cin >> ch;
		exit(-1);
	}
/*
	if (dir != 'L' || dir != 'R' ) {
		cout << "\n Invalid direction \n";
		cin >> ch;
		exit(-1);
	}
	*/
	transitionTo tempTransition;
	tempTransition.state = nextState;
	tempTransition.symbol = symbolOut;
	tempTransition.dir = (dir == 'L') ? L : R;

	//check if we already have this output state
	bool found = 0;
	for (auto iter = m_TT.begin(); iter != m_TT.end(); ++iter) {
		if (iter->dir == tempTransition.dir &&
			iter->state == tempTransition.state &&
			iter->symbol == tempTransition.symbol) {

			found = 1; pos = iter - m_TT.begin();
			break;
		}

	}

	//if this state is not already present then push it into the vector
	if (found == 0) {
		m_TT.push_back(tempTransition);
		pos = m_TT.size() - 1;
	}
	m_transition[prevState][symbolIn] = pos;

}

}

bool TuringMachine::interpreter() {

	string inputStr;
	int currIndex;
	transitionTo currSteps;
	char currState = m_startState, nextState = 'R';
	char symbol;
	direction dir;
	char ch;

	// get the string to be interpreted from the user
	cout << "Enter the input string";
	cin >> inputStr;

	bool valid = false;
	for (int i = 0; i < inputStr.length(); i++) {
		valid = false;
		for (int j = 0; j < m_numAlphabets; j++) {
			if (inputStr.c_str()[i] == m_alphabet[j]) {
				valid = true;
				break;
			}
		}
		if (valid == false) {
			cout << "\n Invalid value !";
			cin >> ch;
			exit(-1);
		}
	}
	

	//store the string into TM's tape
	m_tape.head = 0;
	m_tape.memory.resize(inputStr.length());
	copy(inputStr.c_str(), inputStr.c_str() + inputStr.length(), m_tape.memory.begin());
	m_tape.memory.push_back(BLANK);

	while (m_tape.head != m_tape.memory.size()) {
		//start reading the transition table and processing the string
		currIndex = m_transition[currState][m_tape.memory[m_tape.head]];
		currSteps = m_TT[currIndex];
		nextState = currSteps.state;
		symbol = currSteps.symbol;
		dir = currSteps.dir;

		m_tape.memory[m_tape.head] = symbol;
		if (dir == L) {
			if (m_tape.head == 0) {
				nextState = REJ;
				return false;
			}
			else {
				m_tape.head--;
			}
		}
		else if (dir == R) {
			m_tape.head++;
		}
		currState = nextState;
		if ((nextState == ACC) && symbol == BLANK) {
			return true;
		}
	}

	return false;

}
























	