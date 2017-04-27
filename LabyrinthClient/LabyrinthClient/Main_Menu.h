#pragma once
#include "Game_State.h"

class Main_Menu : public Tiny_State
{
public:
	Main_Menu();
	void initialize(sf::RenderWindow* window);
	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
	void destroy(sf::RenderWindow* window);
	~Main_Menu();
protected:
	int selected;
	sf::Font font, logoFont;
	sf::Text logo, play, quit;
	int up, down;
};

