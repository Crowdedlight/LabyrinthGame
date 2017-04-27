#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

class Tiny_State
{
public:
	virtual void initialize(sf::RenderWindow* window)
	{}
	virtual void update(sf::RenderWindow* window)
	{}
	virtual void render(sf::RenderWindow* window)
	{}
	virtual void destroy(sf::RenderWindow* window)
	{}
	virtual bool requestRecieved(std::vector<unsigned char> input)
	{
		//placeholder
		return true;	
	}
protected:
};

class Game_State
{
public:
	Game_State();
	void setWindow(sf::RenderWindow* window);
	void setState(Tiny_State* state);
	void update();
	Tiny_State* getState();

	~Game_State();

protected:
	sf::RenderWindow* window;
	Tiny_State* state;
};

extern Game_State coreState;
extern bool quitGame;