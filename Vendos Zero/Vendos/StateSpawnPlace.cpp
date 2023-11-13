#include "StateSpawnPlace.h"

StateSpawnPlace::StateSpawnPlace(GraphicsData* graphicsData, std::stack<State*>* Stat)
	: State(graphicsData, Stat)
{
	initPlayer();
	initGraphics();
	initEquipment(graphicsData);

}

StateSpawnPlace::~StateSpawnPlace()
{
	//for (auto* elem : GraphicsSprite)
	//	delete elem;
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

	LoadNewGraph({ 44 * 10, 44 * 12 }, "Tree1");
	LoadNewGraph({ 44 * 13, 44 * 12 }, "Tree2");
	LoadNewGraph({ 44 * 15, 44 * 12 }, "Tree3");

	this->Camer = new Camera(this->graphicsData->GraphicsSprite ,this->SpritesEntiPointer,this->graphicsData->window);

}

void StateSpawnPlace::initPlayer()
{
	this->entiesPointer->push_back(new EntityPlayer({ 44*4,44*20}, "Abigail", SpritesEntiPointer,this->graphicsData->TexturesMap,this->graphicsData->window));
}

void StateSpawnPlace::initBlockade()
{
	int x = this->graphicsData->GraphicsSprite->back()->getGlobalBounds().width;
	int y = this->graphicsData->GraphicsSprite->back()->getGlobalBounds().height;
	
	this->Blockade.resize((x - (x % 44)) / 44, std::vector<bool>((y - (y % 44)) / 44));
	this->BlockadeDimension.resize((x - (x % 44)) / 44, std::vector<sf::Vector2f>((y - (y % 44)) / 44));
}

void StateSpawnPlace::initEquipment(GraphicsData* graphicsData)
{
	this->equipmentPtr = new Equipment(graphicsData);
}

void StateSpawnPlace::update(const float& dt)
{
	this->updateKeybinds(dt);
	this->getMousePosition();
	this->equipmentPtr->update();
}

void StateSpawnPlace::render(sf::RenderTarget* Window)
{
	Camer->render(this->graphicsData->window);
	equipmentPtr->render();
}
