#include "StateSpawnPlace.h"

StateSpawnPlace::StateSpawnPlace(sf::RenderWindow* window, std::stack<State*>* Stat, std::map<std::string, sf::Texture*>* TexturesMap, std::vector<sf::Texture*>* GraphicsTxtVecToP)
	: State(window, Stat, TexturesMap, GraphicsTxtVecToP)
{
	initPlayer();
	initGraphics();
}

StateSpawnPlace::~StateSpawnPlace()
{
	for (auto* elem : GraphicsSprite)
		delete elem;
}

void StateSpawnPlace::updateKeybinds(const float& dt)
{
	this->checkForQuit();
	if (this->Camer->movementAll(dt,this->Blockade,this->BlockadeDimension,100))
	{
		this->Camer->sortVector();
	};
}

void StateSpawnPlace::endState()
{
	std::cout << "Ending SpawnPlaceState\n";
}

void StateSpawnPlace::initGraphics()
{
	LoadNewGraph({ 0,2596}, "Mapka");

	initBlockade();

	LoadNewGraph({ 44 * 6, 44 * 13 }, "Tree1");

	LoadNewGraph({ 44 * 7, 44 * 13 }, "Tree1");
	LoadNewGraph({ 44 * 8, 44 * 13 }, "Tree1");



	this->Camer = new Camera(&this->GraphicsSprite,this->SpritesEntiPointer,window);

}

void StateSpawnPlace::initPlayer()
{
	this->entiesPointer->push_back(new EntityPlayer({ 44*4,44*20}, "Abigail", SpritesEntiPointer,TexturesMap,window));
}

void StateSpawnPlace::initBlockade()
{
	int x = this->GraphicsSprite.back()->getGlobalBounds().width;
	int y = this->GraphicsSprite.back()->getGlobalBounds().height;
	
	this->Blockade.resize((x - (x % 44)) / 44, std::vector<bool>((y - (y % 44)) / 44));
	this->BlockadeDimension.resize((x - (x % 44)) / 44, std::vector<sf::Vector2f>((y - (y % 44)) / 44));
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
