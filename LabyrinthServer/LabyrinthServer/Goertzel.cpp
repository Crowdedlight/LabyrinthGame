
#include "Goertzel.h"

////////////////////////////////////////////////////////////
/*
The constructor creates an array containing the window function.
The size of this array is determined by the parameter anS.
*/
Goertzel::Goertzel(int anS)
	: S(anS)
{
	double cut = 0.5;			// Cut off value (fraction of sample amounts)
	windowF = new double[S];	// Array to hold the window function

	// Generate the window function
	for (int i = 0; i < S*cut; i++)
		windowF[i] = (-2 / (pow(cut*S,3))) * pow(i,3) + (3 / (pow(cut*S,2))) * pow(i,2);
	for (int i = S*cut; i < S*(1 - cut); i++)
		windowF[i] = 1;
	for (int i = S*(1 - cut); i < S; i++)
		windowF[i] = (2 / (pow(cut*S,3))) * pow(i,3) + ((4 * (cut - 3)) / (pow(cut,3)*pow(S,2)) - ((cut - 6) / (pow(cut,3)*pow(S,2)))) * pow(i,2) + ((2 * (cut - 3)) / (pow(cut,3)*S) - (4 * (2 * cut - 3)) / (pow(cut,3)*S)) * i + ((4 * (cut - 1)) / (pow(cut,3)) - (cut - 2) / (pow(cut,3)));

	/*double alpha = 0.16;
	double a0 = (1 - alpha) / 2, a1 = 1 / 2, a2 = alpha / 2;

	for (int i = 0; i < S; i++) {
		windowF[i] = a0 - a1 * cos(2 * PI * i / (S-1)) + a2 * cos(4 * PI * i / (S-1));
	}*/
}
////////////////////////////////////////////////////////////
Goertzel::~Goertzel()
{
	delete windowF;
}
////////////////////////////////////////////////////////////
/*
This method applies the Goertzel algorithm to the supplied data.
The variable S defines how many samples will be includes in the 
analyzis. The parameter startIndex is used to ofset the analysis
from the begining of the vector of samples. This is usefull as
the first and last samples of each tone will be disregarded, to
acount for possible assynchronization between sender and reciever.
*/
int Goertzel::testFrequency(std::vector<sf::Int16> data, unsigned int startIndex)
{
	if (data.size() < startIndex + S - 1)	// If not enough samples return -2
		return -2;

	unsigned long long magnitude[8];	// Temporary array to hold relative magnitudes of the frequencys	
	for (int i = 0; i < 8; i++)			// Check for each frequency
	{
		double k, w, Q0, Q1, Q2;
		k = round(0.5 + (N[i] * DTMF_tjek[i] / Fs));
		w = 2 * cos(2 * PI * k / N[i]);
		Q0 = 0, Q1 = 0, Q2 = 0;

		for (int j = 0; j < S; j++)
		{
			Q0 = (w * Q1) - Q2 + (data.at(startIndex + j)*windowF[j]); 
			Q2 = Q1;
			Q1 = Q0;
		}
		magnitude[i] = (Q1 * Q1) + (Q2 * Q2) - (Q1 * Q2 * w);
	}

	//printMagnitude(magnitude);		// Used for debug and calibration
	return findNumber(magnitude);	// Return number corresponding to the magnitudes
}
////////////////////////////////////////////////////////////
/*
This method prints the magnitudes suplied as the parameter
*/
void Goertzel::printMagnitude(unsigned long long Mag[])
{
	std::cout << "Magnetude of the frequencies: " << std::endl;

	for (int i = 0; i < 8; i++)
		std::cout << std::setw(15) << DTMF_tjek[i] << "Hz";
	std::cout << std::endl;

	for (int i = 0; i < 8; i++)
		std::cout << std::setw(17) << Mag[i];
	std::cout << std::endl;
}
////////////////////////////////////////////////////////////
/*
This method determines which tone corresponds to the 
suplied magnitudes. If the magnitudes are too low, the number -1
will be returned. Otherwise the number of the tone will be returned
*/
int Goertzel::findNumber(unsigned long long mag[])
{
	unsigned long long int tempMag = 0;
	int indexLow = 0, indexHigh = 0;

	// Find index of low frequency
	for (int i = 0; i < 4; i++)
	{
		if (tempMag < mag[i])
		{
			indexLow = i;
			tempMag = mag[i];
		}
	}

	// Find index of high frequency
	tempMag = 0;
	for (int i = 4; i < 8; i++)
	{
		if (tempMag < mag[i])
		{
			indexHigh = i;
			tempMag = mag[i];
		}
	}

	// Check if magnitudes of the frequencies are high enough
	if (mag[indexLow] < 10000000 || mag[indexHigh] < 10000000)
		return -1;

	// Return the number corresponding to the frequencies
	switch (indexLow)
	{
	case 0:
		switch (indexHigh)
		{
		case 4: return 0;
		case 5: return 1;
		case 6: return 2;
		case 7: return 3;
		}
	case 1:
		switch (indexHigh)
		{
		case 4: return 4;
		case 5: return 5;
		case 6: return 6;
		case 7: return 7;
		}
	case 2:
		switch (indexHigh)
		{
		case 4: return 8;
		case 5: return 9;
		case 6: return 10;
		case 7: return 11;
		}
	case 3:
		switch (indexHigh)
		{
		case 4: return 12;
		case 5: return 13;
		case 6: return 14;
		case 7: return 15;
		}
	}
}
////////////////////////////////////////////////////////////