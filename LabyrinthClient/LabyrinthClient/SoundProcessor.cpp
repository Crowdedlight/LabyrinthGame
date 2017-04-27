#include "SoundProcessor.h"

////////////////////////////////////////////////////////////
SoundProcessor::SoundProcessor()
{
}
////////////////////////////////////////////////////////////
SoundProcessor::~SoundProcessor()
{
}
////////////////////////////////////////////////////////////
int SoundProcessor::meanSquare(const std::vector<sf::Int16> &data, int offset, int length) // Offset default = 0
{
	if (offset + length > data.size())	// If not sufficient data return -1
		return -1;
	unsigned long long result = 0;
	for (size_t i = 0; i < length; i++)
	{
		result += square(data.at(offset + i));
	}
	result /= length;
	return result;					// Return mean-square value
}
////////////////////////////////////////////////////////////
int SoundProcessor::largestValue(const std::vector<sf::Int16>& data, int offset, int length)
{
	if (offset + length > data.size())	// If not sufficient data return -1
		return -1;
	unsigned int largest = 0;
	for (size_t i = 0; i < length; i++)
		if (abs(data.at(offset + i)) > largest)
			largest = abs(data.at(offset + i));
	return largest;					// Return largest value
}
////////////////////////////////////////////////////////////
int SoundProcessor::square(int etTal)
{
	return etTal*etTal;
}
////////////////////////////////////////////////////////////