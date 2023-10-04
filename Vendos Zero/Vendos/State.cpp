#include "State.h"

State::State(sf::RenderWindow* Window, std::stack<State*> *Stat)
{
	this->window = Window;
	this->stat = Stat;
	this->quit = false;
	this->SpritesEntiPointer = &this->SpritesEnti;
	this->entiesPointer = &this->entities;
	
}

State::~State()
{
	delete window;
	delete NewEntity;
	std::cout << "Usunalem stat\n";
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::getMousePosition()
{
	this->mousePosition.x = sf::Mouse::getPosition().x - this->window->getPosition().x;
	this->mousePosition.y = sf::Mouse::getPosition().y - this->window->getPosition().y;
}

bool State::checkExactPosition(int x,int offsetX,int y,int offsetY)
{
		return (mousePosition.x > x && mousePosition.x < offsetX && mousePosition.y>y && mousePosition.y < offsetY);
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit = true;
	}
}
