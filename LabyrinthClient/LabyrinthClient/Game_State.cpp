#include "Game_State.h"


Game_State::Game_State()
{
}

void Game_State::setWindow(sf::RenderWindow* window)
{
	this->window = window;
}

Tiny_State* Game_State::getState()
{
	return state;
}

void Game_State::setState(Tiny_State* state)
{
	if (this->state != NULL)
	{
		this->state->destroy(this->window);
		delete this->state;
	}
	this->state = state;
	if (this->state != NULL)
	{
		this->state->initialize(this->window);
	}
}

void Game_State::update()
{
	if (this->state != NULL)
	{
		this->state->update(this->window);
		this->state->render(this->window);
	}
}

Game_State::~Game_State()
{
	if (this->state != NULL)
		delete this->state;
}
