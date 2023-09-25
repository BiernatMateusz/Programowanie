#include "StateSpawnPlace.h"

StateSpawnPlace::StateSpawnPlace(sf::RenderWindow* window, std::stack<State*>* Stat)
	: State(window, Stat)
{
	initGraphics();
}

StateSpawnPlace::~StateSpawnPlace()
{
	for (auto& elem : GraphicsSprite)
		delete elem;
	for (auto& elem : GraphicsTxtVec)
		delete elem;
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
	//Map
	this->GraphicsTxtVec.push_back(new sf::Texture);
	this->GraphicsTxtVec.back()->loadFromFile("Texture/Mapka.png");
	GraphicsSprite.push_back(new sf::Sprite);
	this->GraphicsSprite.back()->setTexture(*this->GraphicsTxtVec.back());

	//Tree
	this->GraphicsTxtVec.push_back(new sf::Texture);
	this->GraphicsTxtVec.back()->loadFromFile("Texture/Tree1.png");
	GraphicsSprite.push_back(new sf::Sprite);
	this->GraphicsSprite.back()->setTexture(*this->GraphicsTxtVec.back());
	this->GraphicsSprite.back()->setPosition(308,88);
	
	//TestSzer
	this->GraphicsTxtVec.push_back(new sf::Texture);
	this->GraphicsTxtVec.back()->loadFromFile("Texture/TestSzer.png");
	GraphicsSprite.push_back(new sf::Sprite);
	this->GraphicsSprite.back()->setTexture(*this->GraphicsTxtVec.back());
	this->GraphicsSprite.back()->setPosition(308, 616);
}

void StateSpawnPlace::update(const float& dt)
{
	this->updateKeybinds(dt);
	this->getMousePosition();
}

void StateSpawnPlace::render(sf::RenderTarget* Window)
{
	for (auto& elem : GraphicsSprite)
		window->draw(*elem);
	for (int i = 308; i < 800; i += 44)
	{
		GraphicsSprite.back()->setPosition(i, 616);
		window->draw(*GraphicsSprite.back());
	}
}
