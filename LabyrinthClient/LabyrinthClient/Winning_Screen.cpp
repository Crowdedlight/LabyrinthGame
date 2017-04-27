#include "Winning_Screen.h"



Winning_Screen::Winning_Screen()
{
}

void Winning_Screen::initialize(sf::RenderWindow* window)
{
	winTex.loadFromFile("win_screen.png");
	winSprite.setTexture(winTex);
}
void Winning_Screen::update(sf::RenderWindow* window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		coreState.setState(new Main_Menu());
	}
}
void Winning_Screen::render(sf::RenderWindow* window)
{
	window->draw(winSprite);
}
void Winning_Screen::destroy(sf::RenderWindow* window)
{
	
}


Winning_Screen::~Winning_Screen()
{
}
