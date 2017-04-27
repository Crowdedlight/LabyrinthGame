#pragma once
#include <vector>
#include <cmath>
#include <SFML/System.hpp>

class SoundProcessor
{
public:
	SoundProcessor();
	~SoundProcessor();
	int meanSquare(const std::vector<sf::Int16> &data, int offset = 0, int length = 10);
	int largestValue(const std::vector<sf::Int16> &data, int offset = 0, int length = 10);
private:
	int square(int etTal);
};

