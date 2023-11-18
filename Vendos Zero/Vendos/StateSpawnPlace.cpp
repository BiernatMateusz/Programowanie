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
	LoadBackground({ 0,2596}, "Mapka");

	initBlockade();

	initTile({ 44 * 10, 44 * 12 }, "Tree1");
	initTile({ 44 * 13, 44 * 12 }, "Tree2");
	initTile({ 44 * 15, 44 * 12 }, "Tree3");

	for (int i=0;i<Tile.size();++i)
		for (int j = 0; j < Tile[0].size(); ++j)
			if (Tile[i][j] != nullptr)
			{
				std::cout << Tile.at(i).at(j)->blokade << "  " << i << "   " << j << "\n";
			}

	updateBlockades();
	updateTilesSprite();

	this->Camer = new Camera(this->graphicsData);
}

void StateSpawnPlace::initPlayer()
{
	
	this->entiesPointer->push_back(new EntityPlayer({44*4,44*20},"Abigail",this->graphicsData));

}

void StateSpawnPlace::initBlockade()
{
	int x = this->graphicsData->GraphicsSprite->back()->getGlobalBounds().width;
	int y = this->graphicsData->GraphicsSprite->back()->getGlobalBounds().height;

	this->Tile.resize((x - (x % 44)) / 44, std::vector<TilesOnMap*>((y - (y % 44)) / 44));
	for (int i = 0; i < this->Tile.size(); ++i)
		for (int j = 0; j < this->Tile[0].size(); ++j)
		{
			Tile[i][j] = nullptr;
		}
	
	
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
