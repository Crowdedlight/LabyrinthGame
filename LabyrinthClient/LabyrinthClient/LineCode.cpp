#include "LineCode.h"


////////////////////////////////////////////////////////////
/*
Constructor.
*/
LineCode::LineCode()
{
}
////////////////////////////////////////////////////////////
/*
This method maps the supplied characters to the corresponding
set of DTMF tones. It also adds startflag and endflag as well
as escape characters (with help from addBitstuffing).
*/
vector<int> LineCode::charToDTMF(vector<unsigned char> input)
{
	vector<int> outputDTMF;

	// Add startflag
	for (int i = 0; i < 3; i++)
		outputDTMF.push_back(i);

	// Map char to DTMF
	int MSB;
	int LSB;
	for (char charIn : input)
	{
		LSB = charIn & 0b1111;				// Bitwise OR to isolate lower nibble
		MSB = (charIn & 0b11110000) >> 4;	// Bitwise OR and right shifting to isolate upper nibble
		outputDTMF.push_back(MSB);
		outputDTMF.push_back(LSB);
	}

	// Add escape characters
	addBitstuffing(outputDTMF);

	// Add endflag
	for (int i = 0; i < 3; i++)
		outputDTMF.push_back(i);

		return outputDTMF;
}
////////////////////////////////////////////////////////////
/*
This method removes escape characters and maps the DTMF tones
to the corresponding characters.
*/
vector<unsigned char> LineCode::DTMFtoChar(vector<int> input)
{
	vector<unsigned char> outputChar;

	// Remove escape characters
	rmBitstuffing(input);

	// Map DTMF to char
	char MSB;
	char LSB;
	for (int i = 0; i < input.size(); i += 2)
	{
		MSB = input[i];
		LSB = input[i + 1];
		char combined = (MSB << 4) | (LSB & 0b1111);	// Left shifting and bitwise OR to combine upper and lower nibble
		outputChar.push_back(combined);
	}

	return outputChar;
}
////////////////////////////////////////////////////////////
/*
This method adds a 3 as escape characters after each 01.
The name is misleading, as this is not bit stuffing.
*/
void LineCode::addBitstuffing(vector<int> &vec)
{
	for (int i = 4; i < vec.size(); i++)
	{
		if (vec[i] == 1 && vec[i - 1] == 0)
		{
			vec.insert(vec.begin() + i + 1, 3);
		}
	}
}
////////////////////////////////////////////////////////////
/*
This method removes escape characters after each 01.
The name is misleading, as this is not bit stuffing.
*/
void LineCode::rmBitstuffing(vector<int> &vec)
{
	for (int i = 2; i < vec.size(); i++)
	{
		if (vec[i] == 3 && vec[i - 1] == 1 && vec[i - 2] == 0)
			vec.erase(vec.begin()+i); //måske -1 for korrekt position. TJEK
	}
}
////////////////////////////////////////////////////////////
/*
Destructor.
*/
LineCode::~LineCode()
{
}
