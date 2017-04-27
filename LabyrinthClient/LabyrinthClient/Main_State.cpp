#include <stdio.h>
#include "Main_State.h"
#include "Main_Menu.h"
#include "DataLinkLayer.h"

extern DataLinkLayer dllSEND;

Main_State::Main_State()
{
}

void Main_State::initialize(sf::RenderWindow* window)
{

	unknownTex.loadFromFile("Cell.png");
	bombTex.loadFromFile("ExplodedMineCell.png");
	emptyTex.loadFromFile("EmptyCell.png");
	playerTex.loadFromFile("player.png");
	playerBombTex.loadFromFile("player_mine.png");
	flaggedCell.loadFromFile("FlaggedCell.png");
	finish.loadFromFile("Finish.png");
	
	// Lost screen
	lostTex.loadFromFile("lost.png");
	lostSprite.setTexture(lostTex);

	//Font 
	this->font.loadFromFile("Montserrat.ttf");

	//Text
	this->lives = sf::Text("Lives: 3", font, 40u);
	this->lives.setPosition(400, 0);
}

void Main_State::resetOnBomb()
{

	Lives--;
	sf::sleep(sf::milliseconds(500));
	mazeDefault[positionY][positionX] = 5;
	positionX = 0;
	positionY = 0;

	//Reset position to start position and replace texture visited with unvisited
	for (int y = 0; y < sizeOfMazeY; y++)
	{
		for (int x = 0; x < sizeOfMazeX; x++)
		{
			if (mazeDefault[y][x] == 1)
			{
				mazeDefault[y][x] = 0;
			}
		}
	}
}

bool Main_State::requestRecieved(vector<unsigned char> data)
{
	//cout << "REQUEST" << endl;
	mazeDefault[positionY][positionX] = data[0];
	msgReturned = true;

	return true;
}

void Main_State::movementUpdate(std::string enS)
{
	if (enS == "w")
	{

		if (positionY > 0 && mazeDefault[positionY-1][positionX] != 5)
		{
			mazeDefault[positionY][positionX] = 1;
			positionY--;

			// Get next cell from server
			//send data to datalink layer positionY-1, positionX;
			unsigned char nextY = positionY;
			unsigned char nextX = positionX;
			dllSEND.receiveData({ nextY,nextX },2);
			msgReturned = false;

			while (!msgReturned)
			{
				sf::sleep(sf::milliseconds(5));//wait until data recieved
			}
			// Cell returned update array

			if (mazeDefault[positionY][positionX] == 2) //Bomb tile
			{
				// Reset position, unvisited tiles and place flag
				resetOnBomb();
			}
			if (mazeDefault[positionY][positionX] == 6)
			{
				won = true;
			}
		}
	}
	else if (enS == "a")
	{
		if (positionX > 0 && mazeDefault[positionY][positionX-1] != 5)
		{
			mazeDefault[positionY][positionX] = 1;
			positionX--;

			// Get next cell from server
			//send data to datalink layer positionY-1, positionX;
			unsigned char nextY = positionY;
			unsigned char nextX = positionX;
			dllSEND.receiveData({ nextY,nextX }, 2);
			msgReturned = false;

			while (!msgReturned)
			{
				sf::sleep(sf::milliseconds(5));//wait until data recieved
			}
			// Cell returned update array

			if (mazeDefault[positionY][positionX] == 2) //Bomb tile
			{
				// Reset position, unvisited tiles and place flag
				resetOnBomb();
			}
			if (mazeDefault[positionY][positionX] == 6)
			{
				won = true;
			}
		}
	}
	else if (enS == "s")
	{
		if (positionY < sizeOfMazeY - 1 && mazeDefault[positionY+1][positionX] != 5)
		{
			mazeDefault[positionY][positionX] = 1;
			positionY++;

			// Get next cell from server
			//send data to datalink layer positionY-1, positionX;
			unsigned char nextY = positionY;
			unsigned char nextX = positionX;
			dllSEND.receiveData({ nextY,nextX }, 2);
			msgReturned = false;

			while (!msgReturned)
			{
				sf::sleep(sf::milliseconds(5));//wait until data recieved
			}
			// Cell returned update array


			if (mazeDefault[positionY][positionX] == 2) //Bomb tile
			{
				// Reset position, unvisited tiles and place flag
				resetOnBomb();
			}
			if (mazeDefault[positionY][positionX] == 6)
			{
				won = true;
			}
		}
	}
	else if (enS == "d")
	{
		if (positionX < sizeOfMazeX - 1 && mazeDefault[positionY][positionX+1] != 5)
		{
			mazeDefault[positionY][positionX] = 1;
			positionX++;

			// Get next cell from server
			//send data to datalink layer positionY-1, positionX;
			unsigned char nextY = positionY;
			unsigned char nextX = positionX;
			dllSEND.receiveData({ nextY,nextX }, 2);
			msgReturned = false;
			//cout << "STARTER LOOP" << endl;
			while (!msgReturned)
			{
				sf::sleep(sf::milliseconds(5));//wait until data recieved
			}
			// Cell returned update array
			//cout << "nået videre" << endl;
			if (mazeDefault[positionY][positionX] == 2) //Bomb tile
			{
				// Reset position, unvisited tiles and place flag
				resetOnBomb();
			}
			if (mazeDefault[positionY][positionX] == 6)
			{
				won = true;
			}
		}
	}
	mazeDefault[positionY][positionX] = 3;
}

void Main_State::update(sf::RenderWindow* window)
{
	//If lost due to lives
	if (Lives == 0)
	{
		lost = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		coreState.setState(new Main_Menu());
	}
	if (won)
	{
		won = false;	
		coreState.setState(new Winning_Screen());
	}

	if (!lost)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !up)
		{
			this->movementUpdate("w");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !left)
		{
			this->movementUpdate("a");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && !down)
		{
			this->movementUpdate("s");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !right)
		{
			this->movementUpdate("d");
		}

		up = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
		left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
		down = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
		right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
	}
	this->levelUpdateInt();
}
void Main_State::render(sf::RenderWindow* window)
{
	this->lives.setString("Lives: " + std::to_string(Lives));

	levelRenderDraw(window);
	window->draw(this->lives);

	if (lost)
	{
		window->draw(lostSprite);
	}

}
void Main_State::destroy(sf::RenderWindow* window)
{
}


void Main_State::levelRenderDraw(sf::RenderWindow* window)
{
	for (int y = 0; y < sizeOfMazeY; y++)
	{
		for (int x = 0; x < sizeOfMazeX; x++)
		{
			window->draw(level[y][x]);
		}

	}
}

void Main_State::levelUpdateInt()
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

Main_State::~Main_State()
{
}
