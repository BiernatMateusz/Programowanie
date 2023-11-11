#include "StateSpawnPlace.h"

StateSpawnPlace::StateSpawnPlace(sf::RenderWindow* window, std::stack<State*>* Stat)
	: State(window, Stat)
{
	this->entiesPointer->push_back(new EntityPlayer("Abigail",SpritesEntiPointer));
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
	GraphicsSprite.back()->setPosition(0, -0.001f);
	this->GraphicsSprite.back()->setTexture(*this->GraphicsTxtVec.back());

	//Tree
	this->GraphicsTxtVec.push_back(new sf::Texture);
	this->GraphicsTxtVec.back()->loadFromFile("Texture/Tree1.png");
	GraphicsSprite.push_back(new sf::Sprite);
	this->GraphicsSprite.back()->setTexture(*this->GraphicsTxtVec.back());
	this->GraphicsSprite.back()->setPosition(308,682);

	//Tree2
	this->GraphicsTxtVec.push_back(new sf::Texture);
	this->GraphicsTxtVec.back()->loadFromFile("Texture/Tree1.png");
	GraphicsSprite.push_back(new sf::Sprite);
	this->GraphicsSprite.back()->setTexture(*this->GraphicsTxtVec.back());
	this->GraphicsSprite.back()->setPosition(200, 228);

	//Tree3
	this->GraphicsTxtVec.push_back(new sf::Texture);
	this->GraphicsTxtVec.back()->loadFromFile("Texture/Tree1.png");
	GraphicsSprite.push_back(new sf::Sprite);
	this->GraphicsSprite.back()->setTexture(*this->GraphicsTxtVec.back());
	this->GraphicsSprite.back()->setPosition(200, 328);

	//Tree4
	this->GraphicsTxtVec.push_back(new sf::Texture);
	this->GraphicsTxtVec.back()->loadFromFile("Texture/Tree1.png");
	GraphicsSprite.push_back(new sf::Sprite);
	this->GraphicsSprite.back()->setTexture(*this->GraphicsTxtVec.back());
	this->GraphicsSprite.back()->setPosition(200, 428);
	

	this->Camer = new Camera(&this->GraphicsSprite,this->SpritesEntiPointer,window);

}

void StateSpawnPlace::initPlayer()
{

}

void StateSpawnPlace::update(const float& dt)
{
	this->updateKeybinds(dt);
	this->getMousePosition();
}

void StateSpawnPlace::render(sf::RenderTarget* Window)
{
	Camer->render(window);
}
