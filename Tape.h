#pragma once

#include <vector>

#define INFINITE_SIZE 100
class Tape
{
public:
	Tape();
	~Tape();

	std::vector<char> memory;
	int head;

};

