#include <stdio.h>
#include "Random_Maze.h"
#include "Main_Menu.h"

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
		coreState.setState(new Main_Menu());
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
			default:
				continue;
			}
			level[y][x].setPosition(sf::Vector2f(24 * x, 24 * y));  //consider if the position could be set only once as it's a fixed grid
		}
	}
}

Random_Maze::~Random_Maze()
{
}
