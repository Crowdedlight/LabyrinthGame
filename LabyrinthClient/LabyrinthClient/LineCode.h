#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
class LineCode
{
public:
	LineCode();
	vector<int> charToDTMF(vector<unsigned char> inputChar);	// LineCoding and flags
	vector<unsigned char> DTMFtoChar(vector<int> inputDTMF);	// LineDecoding
	~LineCode();

protected:
	void addBitstuffing(vector<int> &vec);		// Adds escape characters
	void rmBitstuffing(vector<int> &vec);		// Remove escape characters

};

