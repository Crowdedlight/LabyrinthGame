#include "MapGenerator.h"
#include <algorithm>


MapGenerator::MapGenerator()
{
}

void MapGenerator::resetMap()
{
	//Resets map too all bombs for the path finder algorthm to work properly

	for (int y = 0; y < sizeOfMazeY; y++)
	{
		for (int x = 0; x < sizeOfMazeX; x++)
		{
			mazeBomb[y][x] = 2;
		}
	}

	//Erase path, maybe better way of doing it?
	for (auto i : path)
		path.pop_back();
}

void MapGenerator::generate()
{
	bool pathFound = false;
	resetMap();

	currentX = startX;
	currentY = startY;
	setVisited(currentX, currentY);

	while (unvisitedLeft())
	{

		if (unvisitedNeighbours().size() != 0)
		{			
			//Push current cell to stack
			mazeBomb[currentY][currentX] = 0;
			stack.push_back(coords(currentX, currentY));

			if (!pathFound)
			{
				path.push_back(coords(currentX, currentY));
				if (currentX == 0 && currentY == 1)
					pathFound = true;
			}

			//Move random direction
			randomMoveNeighbour(unvisitedNeighbours());
			
			//set new cell as visited
			setVisited(currentX, currentY);

		}
		else if (stack.size() != 0)
		{
			//Set current cell to last cell
			currentX = stack.back().x;
			currentY = stack.back().y;

			//pop this cell
			stack.pop_back();
			if (!pathFound && path.size() != 0)
				path.pop_back();
		}
		else
		{
			cout << "ELSE" << endl;
			bool run = true;
			while (run)
			{
			mt19937 gen(rd());
			uniform_int_distribution<> distX(0, sizeOfMazeX);
			uniform_int_distribution<> distY(0, sizeOfMazeY);
				int tempX = distX(gen);
				int tempY = distY(gen);

				if (!mazeVisited[tempY][tempX])
				{
					currentX = tempX;
					currentY = tempY;
					setVisited(currentX, currentY);
					run = false;
				}
			}

		}


	}

	//In the few cases where our starting position is a bomb replace bomb with player
	//Actually have to manually place the player for each run
	//Testing trying to set player at last stack entry as that must always give a way though
//	int tempY = stack.size() / 2;
//	int tempX = stack.size() / 2;
//	cout << path.size() << endl;

//	for (auto i : path)
//	{
//		mazeBomb[i.y][i.x] = 1;
//	}

	mazeBomb[0][0] = 3;		//player start position
	mazeBomb[9][14] = 6;	//Goal
}

void MapGenerator::randomMoveNeighbour(vector<string> neighbours)
{
	//Random number from unvisited neighbour
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, unvisitedNeighbours().size()-1);

	//Check directions
	// North
	if (neighbours[dist(gen)] == "N")
	{
		currentX += 0;
		currentY -= 1;
	}
	// South
	if (neighbours[dist(gen)] == "S")
	{
		currentX += 0;
		currentY += 1;
	}
	// West
	if (neighbours[dist(gen)] == "W")
	{
		currentX -= 1;
		currentY += 0;
	}
	// East
	if (neighbours[dist(gen)] == "E")
	{
		currentX += 1;
		currentY += 0;
	}
}

bool MapGenerator::unvisitedLeft()
{
	for (int y = 0; y < sizeOfMazeY; y++)
	{
		for( int x = 0; x < sizeOfMazeX; x++)
		{
			if (!mazeVisited[y][x])
				return true;
		}
	}
	return false;
}
bool MapGenerator::isVisited(int cellX, int cellY)
{
	if (mazeVisited[cellY][cellX])
		return true;
	return false;
}
void MapGenerator::setVisited(int cellX, int cellY)
{
	mazeVisited[cellY][cellX] = true;
}
vector<string> MapGenerator::unvisitedNeighbours()
{
	//Using current X,Y coords
	
	vector<string> unVisited;

	//North
	if (!mazeVisited[currentY - 1][currentX] && (currentY - 1) >= 0)
		unVisited.push_back("N");
	//South
	if (!mazeVisited[currentY + 1][currentX] && (currentY + 1) < sizeOfMazeY)
		unVisited.push_back("S");
	//West
	if (!mazeVisited[currentY][currentX-1] && (currentX - 1) >= 0)
		unVisited.push_back("W");
	//East
	if (!mazeVisited[currentY][currentX+1] && (currentX + 1) <= sizeOfMazeX)
		unVisited.push_back("E");

	return unVisited;
}

MapGenerator::~MapGenerator()
{
}
