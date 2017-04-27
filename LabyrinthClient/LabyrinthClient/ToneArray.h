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

#define sek 0.025			// Length of tone
#define sampleRate 8000
#define pi 3.14159265359

class ToneArray
{
public:
	ToneArray();
	void playBuffer(vector<int> digits);	// Plays the suppplied tones
	~ToneArray();
protected:
	void windowFunc();
	double getDigitLow(int enInt);			// Returns the high frequency 
	double getDigitHigh(int enInt);			// Returns the low frequency
	int antalSamples = sampleRate*sek;		// Samples per tone
	double *windowF;						// Pointer to array that stores the window function
	vector<sf::Int16> bufferSend;			// Array to temporarily hold the signal to be send
	double ampli = 15000;					// Amplitude of each frequency
};