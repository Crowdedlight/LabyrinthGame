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
	vector<int> charToDTMF(vector<unsigned char> inputChar);
	vector<unsigned char> DTMFtoChar(vector<int> inputDTMF);
	~LineCode();

protected:
	void addBitstuffing(vector<int> &vec);
	void rmBitstuffing(vector<int> &vec);

};

