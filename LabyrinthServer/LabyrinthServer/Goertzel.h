#pragma once
#include <vector>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>
#include <iomanip>

class Goertzel
{
public:
	Goertzel(int anS);
	~Goertzel();

	int testFrequency(std::vector<sf::Int16> data, unsigned int startIndex);
private:
	void printMagnitude(unsigned long long mag[]);	// Prints the relative magnitudes
	int findNumber(unsigned long long mag[]);		// Returns the number corresponding to the detected magnitudes

	int const DTMF_tjek[8] = { 697, 770, 852, 941, 1207, 1336, 1477, 1633 };
	const unsigned int N[8] = { 253,   229,   207,   187,   146,   132,   119,   108 };
	//const unsigned int N[8] = { 230,   208,   188,   170,   133,   120,   108,   98 };
	const unsigned int Fs = 8000;			// Sampling frequency	
	const unsigned int S;					// Amount of samples to be considered in each analyzis
	const double PI = 3.141592653589793238463;
	double * windowF;
};

