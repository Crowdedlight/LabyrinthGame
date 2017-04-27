#include "Game_State.h"
#include "Random_Maze.h"
#include <iostream>
#include <Windows.h>
#include <thread>
#include "PhysicalLayer.h"
#include "DataLinkLayer.h"
#include <mutex>

Game_State coreState;
bool quitGame = false;

unsigned char DllFrame::frameNum = 0;
unsigned char DataLinkLayer::latestFrameSent = 55;

mutex mut;
DataLinkLayer dllSEND, dllREC;
PhysicalLayer pl;


int main()
{

	//create window
	sf::RenderWindow window(sf::VideoMode(600, 400), "Labyrint", sf::Style::Titlebar | sf::Style::Close);

	coreState.setWindow(&window);
	coreState.setState(new Random_Maze());
	
	//Layers
	pl.setDLL(&dllREC);
	dllSEND.setPtr(coreState.getState(), pl, dllREC, mut);
	dllREC.setPtr(coreState.getState(), pl, dllSEND, mut);

	thread dllS_t{ &DataLinkLayer::waitDLL,&dllSEND };
	thread dllR_t{ &DataLinkLayer::waitDLL,&dllREC };
	thread pl_t{ &PhysicalLayer::activate,&pl };


	//Run program as long as window is open
	while (window.isOpen())
	{
		//check all the windows events that were triggered since last iteraton
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		coreState.update();

		window.display();

		if (quitGame)
		{
			window.close();
		}

		Sleep(5);
	}

	return 0;
}