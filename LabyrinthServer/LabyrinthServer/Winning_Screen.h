#pragma once
#include "Game_State.h"
#include "Random_Maze.h"

class Winning_Screen : public Tiny_State
{
public:
	Winning_Screen();
	void initialize(sf::RenderWindow* window);
	void update(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
	void destroy(sf::RenderWindow* window);
	~Winning_Screen();
protected:
	sf::Texture winTex;
	sf::Sprite winSprite;
};