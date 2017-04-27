#include "Game_State.h"
#include <iostream>

const int sizeOfMazeX = 15;
const int sizeOfMazeY = 10;
int positionX = 0;
int positionY =	1;
int mazeDefault[sizeOfMazeY][sizeOfMazeX] = 
{ 
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
};

sf::Sprite level[sizeOfMazeY][sizeOfMazeX];

// ADD UPDATE MAP FUNCTION IN ACTION CLASS

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


/*
Game_State coreState;

int main()
{

	//create window
	sf::RenderWindow window(sf::VideoMode(600, 400), "Labyrint", sf::Style::Titlebar | sf::Style::Close);

	coreState.setWindow(&window);

	window.setTitle("Labyrint");
	window.setFramerateLimit(60);

	sf::Texture unknownTex;
	unknownTex.loadFromFile("Cell.png");

	sf::Texture bombTex;
	bombTex.loadFromFile("ExplodedMineCell.png");

	sf::Texture emptyTex;
	emptyTex.loadFromFile("EmptyCell.png");

	sf::Texture playerTex;
	playerTex.loadFromFile("player.png");

	sf::Texture playerBombTex;
	playerBombTex.loadFromFile("player_mine.png");

	//Action Class for movement and updates

	// run the program as long as the window is open
	while (window.isOpen())
	{

		// check all the windows events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			// "close requested" event: we close the window
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyReleased:
				//update / movement

				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					window.close();
					break;
				case sf::Keyboard::D:
					//Move to class and make an "collision() function that have functionality to update texture and properties
					if (positionX < sizeOfMazeX -1)
					{
						mazeDefault[positionY][positionX] = 1;
						positionX++;
					}
					break;

				case sf::Keyboard::A:
					if (positionX > 0)
					{
						mazeDefault[positionY][positionX] = 1;
						positionX--;
					}
					break;

				case sf::Keyboard::W:
					if (positionY > 0)
					{
						mazeDefault[positionY][positionX] = 1;
						positionY--;
					}
					break;

				case sf::Keyboard::S:
					if (positionY < sizeOfMazeY -1)
					{
						mazeDefault[positionY][positionX] = 1;
						positionY++;
					}
					break;
				}
				mazeDefault[positionY][positionX] = 3;
				break;

			default:
				break;
			}


		}

		//clear the window with black color
		window.clear(sf::Color::Black);

		//draw everything here:
		//Move to Action class Update();

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
				level[y][x].setPosition(sf::Vector2f(24*x, 24*y));
				window.draw(level[y][x]);
			}

		}

		//end the current frame
		window.display();

	}



	return 0;
}
*/