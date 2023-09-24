#include "StateSpawnPlace.h"

StateSpawnPlace::StateSpawnPlace(sf::RenderWindow* window, std::stack<State*>* Stat)
	: State(window, Stat)
{
	initGraphics();
}

StateSpawnPlace::~StateSpawnPlace()
{

}

void StateSpawnPlace::updateKeybinds(const float& dt)
{
	this->checkForQuit();
}

void StateSpawnPlace::endState()
{
	std::cout << "Ending SpawnPlaceState\n";
}

void StateSpawnPlace::initGraphics()
{
	this->GraphicsTxt.loadFromFile("Texture/Mapka.png");
	this->GraphicsSprite.setTexture(this->GraphicsTxt);
}

void StateSpawnPlace::update(const float& dt)
{
	this->updateKeybinds(dt);
	this->getMousePosition();
}

void StateSpawnPlace::render(sf::RenderTarget* Window)
{
	Window->draw(this->GraphicsSprite);
}
