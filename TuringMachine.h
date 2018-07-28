#pragma once

#include<vector>
#include<map>
#include <string>

#include "Tape.h"

#define MAX_STATES 30
#define MAX_ALPHABET_SIZE 30
#define BLANK '$'
#define ACC 'A'
#define REJ 'R'



enum direction { L,R };

struct transitionTo {
	char state; // A and R states reserved for accept and reject
	char symbol;
	direction dir;
};

class TuringMachine
{
public:
	TuringMachine();
	~TuringMachine();
	void readTransitionFile();
	bool interpreter();

	int m_numTapeAlphabets;
	int m_numAlphabets;
	char m_states[MAX_STATES]; // A and R states reserved for accept and reject
	char m_alphabet[MAX_ALPHABET_SIZE]; 
	char m_tapeAlphabet[MAX_ALPHABET_SIZE + 1]; 
	std::map <char, std::map<char, int>> m_transition; // map of state, symbol and index to the TT vector
	std::vector<transitionTo> m_TT;
	char m_startState;	
	Tape m_tape;


};

