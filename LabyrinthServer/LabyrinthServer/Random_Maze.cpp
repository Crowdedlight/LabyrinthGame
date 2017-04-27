#include <stdio.h>
#include "Random_Maze.h"
#include "DataLinkLayer.h"

extern DataLinkLayer dllSEND;

Random_Maze::Random_Maze()
{
}

void Random_Maze::initialize(sf::RenderWindow* window)
{

	unknownTex.loadFromFile("Cell.png");
	bombTex.loadFromFile("ExplodedMineCell.png");
	emptyTex.loadFromFile("EmptyCell.png");
	playerTex.loadFromFile("player.png");
	playerBombTex.loadFromFile("player_mine.png");
	flaggedCell.loadFromFile("FlaggedCell.png");
	finish.loadFromFile("Finish.png");

	//Import randomized maze
	MapGenerator map1;
	map1.generate();
	
	for (int y = 0; y < sizeOfMazeY; y++)
	{
		for (int x = 0; x < sizeOfMazeX; x++)
		{
			mazeDefault[y][x] = map1.mazeBomb[y][x];
		}
	}
}

void Random_Maze::update(sf::RenderWindow* window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		// Exit somehow
		quitGame = true;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !space)
	{

		MapGenerator newMap;
		newMap.generate();
		
		for (int y = 0; y < sizeOfMazeY; y++)
		{
			for (int x = 0; x < sizeOfMazeX; x++)
			{
				mazeDefault[y][x] = newMap.mazeBomb[y][x];
			}
		}
	}

	space = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

	this->levelUpdateInt();
}
void Random_Maze::render(sf::RenderWindow* window)
{
	levelRenderDraw(window);
}
void Random_Maze::destroy(sf::RenderWindow* window)
{
}


void Random_Maze::levelRenderDraw(sf::RenderWindow* window)
{
	for (int y = 0; y < sizeOfMazeY; y++)
	{
		for (int x = 0; x < sizeOfMazeX; x++)
		{
			window->draw(level[y][x]);
		}

	}
}

void Random_Maze::levelUpdateInt()
{
	for (int y = 0; y < sizeOfMazeY; y++)
	{
		for (int x = 0; x < sizeOfMazeX; x++)
		{
			switch (mazeDefault[y][x])
			{
			case 0: // Unknown
				level[y][x].setTexture(unknownTex);
				break;
			case 1: // Visited / Empty
				level[y][x].setTexture(emptyTex);
				break;
			case 2: // Bomb
				level[y][x].setTexture(bombTex);
				break;
			case 3: // player
				level[y][x].setTexture(playerTex);
				break;
			case 4: // player on bomb - might not be the approch 
				level[y][x].setTexture(playerBombTex);
				break;
			case 5: // Flag marking preveiusly bomb
				level[y][x].setTexture(flaggedCell);
				break;
			case 6:
				level[y][x].setTexture(finish);
				break;
			default:
				continue;
			}
			level[y][x].setPosition(sf::Vector2f(24 * x, 24 * y));  //consider if the position could be set only once as it's a fixed grid
		}
	}
}

bool Random_Maze::requestRecieved(vector<unsigned char> recieved)
{
	// char data recieved

	// set old position as visited
	mazeDefault[positionY][positionX] = 1;
	
	for (auto i : recieved)
		cout << i << ",";
	//load new values over
	positionY = recieved[0];
	positionX = recieved[1];

	cout << positionY << "," << positionX << endl;

	//Return type at given coords
	vector<unsigned char> returnValue;
	returnValue.clear();
	returnValue.push_back(mazeDefault[positionY][positionX]);

	sf::sleep(sf::milliseconds(1000));
	dllSEND.receiveData(returnValue,2);

	// Update server viewport //

	//bomb
	if (mazeDefault[positionY][positionX] == 2)
	{
		// Bombe
		mazeDefault[positionY][positionX] = 5;
		// reset player position
		positionY = 0;
		positionX = 0;
	}
	
	if (mazeDefault[positionY][positionX] == 6)
	{
		// Mål
		// reset player position
		positionY = 0;
		positionX = 0;
	}

	//New player position
	mazeDefault[positionY][positionX] = 3;
	return true;
}

Random_Maze::~Random_Maze()
{
}
