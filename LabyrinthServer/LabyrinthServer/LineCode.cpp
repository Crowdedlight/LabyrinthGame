#include "LineCode.h"



LineCode::LineCode()
{
}

vector<int> LineCode::charToDTMF(vector<unsigned char> input)
{
	vector<int> outputDTMF;

	//Tilføj start flag
	for (int i = 0; i < 3; i++)
		outputDTMF.push_back(i);

	for (char charIn : input)
	{
		int MSB;
		int LSB;

		LSB = charIn & 0b1111; //Bit vis OR for at isolerer øverste 4 bits og nederste 4bits 
		MSB = (charIn & 0b11110000) >> 4; //Tilsat bit shifting for at få de 4 bits uden foranstillede nuller

		outputDTMF.push_back(MSB);
		outputDTMF.push_back(LSB);

		//cout << charIn << ",";
	}
	//cout << endl;

	//Lav function call bitstuffing
	addBitstuffing(outputDTMF);

	//Tilføj slut flag
	for (int i = 0; i < 3; i++)
		outputDTMF.push_back(i);

		return outputDTMF;
}

vector<unsigned char> LineCode::DTMFtoChar(vector<int> input)
{
	vector<unsigned char> outputChar;

	rmBitstuffing(input);

	//DEBUG
	//for (auto i : input)
	//	cout << i << ",";

	char MSB;
	char LSB;

	for (int i = 0; i < input.size(); i += 2)
	{
		MSB = input[i];
		LSB = input[i + 1];

		char combined = (MSB << 4) | (LSB & 0b1111);
		outputChar.push_back(combined);
		//cout << combined << ",";
	}
	//cout << endl;
	return outputChar;
}

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

void LineCode::rmBitstuffing(vector<int> &vec)
{
	for (int i = 2; i < vec.size(); i++)
	{
		if (vec[i] == 3 && vec[i - 1] == 1 && vec[i - 2] == 0)
			vec.erase(vec.begin()+i); //måske -1 for korrekt position. TJEK
	}
}

LineCode::~LineCode()
{
}
