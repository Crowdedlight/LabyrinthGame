#pragma once
#include "Game_State.h"
#include "MapGenerator.h"
#include <string>

class Random_Maze : public Tiny_State
{
public:
	Random_Maze();
	void initialize(sf::RenderWindow* window);
	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
	void destroy(sf::RenderWindow* window);
	~Random_Maze();
protected:
	//Function to ask server for next field value
	void levelUpdateInt();
	void levelRenderDraw(sf::RenderWindow* window);
	sf::Sprite level[sizeOfMazeY][sizeOfMazeX];
	sf::Texture unknownTex, bombTex, emptyTex, playerTex, playerBombTex;
	int space;
	int positionX = 0;
	int positionY = 1;
	int mazeDefault[sizeOfMazeY][sizeOfMazeX] =
	{
		{ 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6 },
	};


	/*
	The folliwing will explain the meaning of the intergers in the array mazeDefault[][].
	0: unknown tile
	1: Visited Tile
	2: Bomb Tile
	3: Player
	4: Player on bomb, Rosted player
	5: Flag, marking bomb that killed you last. (3 lives total)
	6:
	7:
	8:
	*/

};

