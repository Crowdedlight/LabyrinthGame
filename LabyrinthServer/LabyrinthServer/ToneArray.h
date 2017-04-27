#pragma once
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>


using namespace std;

#define sek 0.025
#define sampleRate 8000
#define pi 3.14159265359

class ToneArray
{
public:
	ToneArray();
	void playBuffer(vector<int> digits);
	~ToneArray();
protected:
	void windowFunc();
	double getDigitLow(int enInt);
	double getDigitHigh(int enInt);
	int antalSamples = sampleRate*sek;
	double *windowF;
	vector<sf::Int16> bufferSend;
	double ampli = 15000;
};