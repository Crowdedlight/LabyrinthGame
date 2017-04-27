#include "ToneArray.h"



ToneArray::ToneArray()
{
	//Opret window functionen til dæmpning ved start/stop af tonerne. Til playBuffer() elementet. 
	windowFunc();
}

double ToneArray::getDigitLow(int digit)
{
	switch (digit)
	{
	case 0:  case 1:  case 2:  case 3:  return 697.; break;
	case 4:  case 5:  case 6:  case 7:  return 770.; break;
	case 8:  case 9:  case 10: case 11: return 852.; break;
	case 12: case 13: case 14: case 15: return 941.; break;
	}
}

double ToneArray::getDigitHigh(int digit)
{
	switch (digit)
	{
	case 0: case 4: case 8:  case 12: return 1209.; break;
	case 1: case 5: case 9:  case 13: return 1336.; break;
	case 2: case 6: case 10: case 14: return 1477.; break;
	case 3: case 7: case 11: case 15: return 1633.; break;
	}
}

void ToneArray::windowFunc()
{
	double cut = 0.02;
	int S = antalSamples;

	windowF = new double[S];

	for (int i = 0; i < S*cut; i++) {
		windowF[i] = (-2 / (cut*cut*cut*S*S*S)) * i * i * i + (3 / (cut*cut*S*S)) * i * i;
	}
	for (int i = S*cut; i < S*(1 - cut); i++) {
		windowF[i] = 1;
	}
	for (int i = S*(1 - cut); i < S; i++) {
		windowF[i] = (2 / (cut*cut*cut*S*S*S)) * i * i * i + ((4 * (cut - 3)) / (cut*cut*cut*S*S) - ((cut - 6) / (cut*cut*cut*S*S))) * i * i + ((2 * (cut - 3)) / (cut*cut*cut*S) - (4 * (2 * cut - 3)) / (cut*cut*cut*S)) * i + ((4 * (cut - 1)) / (cut*cut*cut) - (cut - 2) / (cut*cut*cut));
	}

}

void ToneArray::playBuffer(vector<int> digits)
{
	for (int intDig : digits)
	{
		for (int i = 0; i < antalSamples; i++)
		{
			double tempTone = (ampli * sin(i * 2 * pi*getDigitLow(intDig) / sampleRate) + ampli * sin(i * 2 * pi*getDigitHigh(intDig) / sampleRate));
			tempTone *= windowF[i];
			bufferSend.push_back(tempTone);
			tempTone = NULL;
		}
	}
	
	//cout << digits.size() << endl;

	sf::SoundBuffer Buffer;
	if (!Buffer.loadFromSamples(&bufferSend[0], (antalSamples*digits.size()), 1, sampleRate)) {
		std::cerr << "Loading failed!" << std::endl;
	}

	sf::Sound Sound;
	Sound.setBuffer(Buffer);
	Sound.setLoop(false);
	Sound.play();

	sf::sleep(sf::seconds(sek*digits.size()));
	bufferSend.clear();
}

ToneArray::~ToneArray()
{
}
