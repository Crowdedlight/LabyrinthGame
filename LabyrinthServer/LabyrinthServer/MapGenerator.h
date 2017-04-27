#pragma once
#include "Random_Maze.h"
#include "coords.h"
#include <vector>
#include <string>
#include <iostream>
#include <random>

using namespace std;

	// const int sizeOfMazeX;
	// const int sizeOfMazeY;

class MapGenerator
{


public:
	MapGenerator();
	void generate();
	~MapGenerator();

	int mazeBomb[sizeOfMazeY][sizeOfMazeX];
protected:
	bool unvisitedLeft();
	bool isVisited(int cellX, int cellY);
	void setVisited(int cellX, int CellY);
	void randomMoveNeighbour(vector<string> neighbours);
	vector<string> unvisitedNeighbours();
	void resetMap();
	int startX = 14; // goal coords
	int startY = 9;
	int currentX, currentY;
	random_device rd;
	vector<coords> stack;
	vector<coords> path;
	bool mazeVisited[sizeOfMazeY][sizeOfMazeX] = { false };

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

