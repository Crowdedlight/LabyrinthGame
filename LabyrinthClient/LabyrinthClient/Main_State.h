#pragma once
#include "Game_State.h"
#include "Winning_Screen.h"
#include <string>
#include <vector>
#include <iostream>
#include <thread>

using namespace std;


//have to set global due to array creation.
const int sizeOfMazeX = 15;
const int sizeOfMazeY = 10;

class Main_State : public Tiny_State
{
public:
	Main_State();
	void initialize(sf::RenderWindow* window);
	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
	void destroy(sf::RenderWindow* window);
	void movementUpdate(std::string enS);
	bool requestRecieved(std::vector<unsigned char> data);
	~Main_State();
protected:
	//Function to ask server for next field value
	void levelUpdateInt();
	void resetOnBomb();
	void levelRenderDraw(sf::RenderWindow* window);
	sf::Sprite level[sizeOfMazeY][sizeOfMazeX];
	sf::Sprite lostSprite;
	sf::Texture unknownTex, bombTex, emptyTex, playerTex, playerBombTex, flaggedCell, finish, lostTex;
	sf::Text lives;
	sf::Font font;
	bool won = false;
	bool lost = false;
	bool msgReturned = false;
	int Lives = 3;
	int up, left, right, down;
	int positionX = 0;
	int positionY = 0;
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
	6: Finish
	*/

};

