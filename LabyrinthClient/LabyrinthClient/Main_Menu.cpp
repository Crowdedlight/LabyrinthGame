#include "Main_Menu.h"
#include "Main_State.h"
#include "Random_Maze.h"
#include "DataLinkLayer.h"
#include <mutex>
#include "PhysicalLayer.h"

extern Game_State coreState;
extern DataLinkLayer dllSEND, dllREC;
extern mutex mut;
extern PhysicalLayer pl;


Main_Menu::Main_Menu()
{
}

void Main_Menu::initialize(sf::RenderWindow* window) //Sætte positioner, textures etc.
{
	this->font.loadFromFile("OuterspaceMilitia.ttf");
	this->logoFont.loadFromFile("Maze.ttf");

	this->logo = sf::Text("Mine Runner", logoFont, 100U);
	this->logo.setOrigin(this->logo.getGlobalBounds().width / 2, 0);
	this->logo.setPosition(window->getSize().x / 2, 0);

	this->play = sf::Text("Play", font, 54U);
	this->play.setOrigin(this->play.getGlobalBounds().width / 2, 0);
	this->play.setPosition(window->getSize().x / 2, this->logo.getGlobalBounds().height * 2.5f);

	this->quit = sf::Text("Quit", font, 54U);
	this->quit.setOrigin(this->quit.getGlobalBounds().width / 2, 0);
	this->quit.setPosition(window->getSize().x / 2, this->logo.getGlobalBounds().height * 2.5f + this->play.getGlobalBounds().height * 2.0f);

	this->selected = 0;
}
void Main_Menu::update(sf::RenderWindow* window) //Checker spil logik, moves, dead, win, etc
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && !down)
	{
		this->selected -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !up)
	{
		this->selected += 1;
	}
	if (this->selected < 0)
	{
		this->selected = 1;
	}
	if (this->selected > 1)
	{
		this->selected = 0;
	}

	up = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
	down = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
	{
		switch (this->selected)
		{
		case 0:
			coreState.setState(new Main_State());
			dllSEND.setPtr(coreState.getState(), pl, dllREC, mut);
			dllREC.setPtr(coreState.getState(), pl, dllSEND, mut);
			break;
		case 1:
			quitGame = true;
			break;
		}
	}

	//Secret mapgenerator
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
	{
		coreState.setState(new Random_Maze());
	}

}
void Main_Menu::render(sf::RenderWindow* window)
{

	this->play.setColor(sf::Color::White);
	this->quit.setColor(sf::Color::White);

	this->play.setString("Play");
	this->quit.setString("Quit");

	switch (this->selected)
	{
	case 0:
		this->play.setColor(sf::Color(128, 0, 0));
		break;
	case 1:
		this->quit.setColor(sf::Color(128, 0, 0));
		break;
	}

	window->draw(this->logo);
	window->draw(this->play);
	window->draw(this->quit);
}
void Main_Menu::destroy(sf::RenderWindow* window)
{

}

Main_Menu::~Main_Menu()
{
}
