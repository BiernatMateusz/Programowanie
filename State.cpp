#include "State.h"

//Constructors
State::State(GraphicsData* graphicsData, std::stack<State*>* Stat)
{
	this->graphicsData = graphicsData;
	this->stat = Stat;
	this->quit = false;
	this->SpritesEntiPointer = new std::vector<sf::Sprite*>;//&this->SpritesEnti;

	// ---GRAPHICS SPRITES
	this->graphicsData->GraphicsSprite = new std::vector<sf::Sprite*>;

	for (auto* elem : *this->graphicsData->GraphicsSprite)
		delete elem;

	this->graphicsData->GraphicsSprite->clear();
	//

	// ---ENTITIES CLASS
	this->entiesPointer = new std::vector<Entity*>;
	//
	
	// ---ENTITIES SPRITES
	this->graphicsData->EntitiesSprite = new std::vector<sf::Sprite*>;

	for (auto* elem : *this->graphicsData->EntitiesSprite)
		delete elem;

	this->graphicsData->EntitiesSprite->clear();
	//

	// ---TILES SPRITES
	this->graphicsData->TilesSprite = new std::vector<sf::Sprite*>;

	for (auto* elem : *this->graphicsData->TilesSprite)
		delete elem;

	this->graphicsData->TilesSprite->clear();
	//

	// ---ITEMS THROWN SPRITES
	this->graphicsData->ItemsThrownSprite = new std::vector<sf::Sprite*>;

	for (auto* elem : *this->graphicsData->ItemsThrownSprite)
		delete elem;

	this->graphicsData->ItemsThrownSprite->clear();
	//

}

//Destructor
State::~State()
{
	delete this->graphicsData->window;
	std::cout << "Usunalem stat\n";
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::getMousePosition()
{
	this->graphicsData->mousePosition = sf::Mouse::getPosition(*this->graphicsData->window);
}

bool State::checkExactPosition(int x,int offsetX,int y,int offsetY)
{
		return (this->graphicsData->mousePosition.x > x && this->graphicsData->mousePosition.x < offsetX && this->graphicsData->mousePosition.y>y && this->graphicsData->mousePosition.y < offsetY);
}

void State::checkForQuit(const std::map<std::string, button*>& AllKeys)
{
	if (AllKeys.at("Esc")->isButtonPressed())
		this->quit = true;
}

void State::initTileAndBlockade()
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

void State::LoadBackground(sf::Vector2f&& position, std::string&& NameOfTxt)
{
	if (this->graphicsData->backGround != nullptr)
		delete this->graphicsData->backGround;

	this->graphicsData->backGround = new sf::Sprite;
	this->graphicsData->GraphicsSprite->push_back(new sf::Sprite);
	this->graphicsData->GraphicsSprite->back()->setTexture(*this->graphicsData->TexturesMap->at(NameOfTxt));

	this->graphicsData->backGround = graphicsData->GraphicsSprite->back();

	initTileAndBlockade();

	//Setting origins
	if (NameOfTxt == "Mapka")
	{
		this->graphicsData->GraphicsSprite->back()->setOrigin(0, this->graphicsData->GraphicsSprite->back()->getGlobalBounds().height);

		

		for (int i=0;i<(int)graphicsData->backGround->getGlobalBounds().width/44;++i)
			for (int j = 0; j < (int)graphicsData->backGround->getGlobalBounds().height/44; ++j)
				if (graphicsData->TextureDataMap->at("Mapka")->blocksOccupied[i][j] == 1)
					this->Tile[i][j] = new TilesOnMap(graphicsData); //creating invisible blocks as a barrier for map 
	}
	this->graphicsData->GraphicsSprite->back()->setPosition(position.x, position.y);

}

void State::initTile(sf::Vector2i&& position2i, std::string&& NameOfTxt)
{
	this->Tile[position2i.x][position2i.y] = new TilesOnMap(position2i,NameOfTxt,graphicsData);

	if (this->graphicsData->TextureDataMap->at(NameOfTxt)->typeOfTile == 8) //8 -> chest
		initChest({ position2i.x,position2i.y});

}


void State::initChest(sf::Vector2i position2i)
{
	this->Tile[position2i.x][position2i.y]->chest = new itemChest(this->graphicsData);
}

void State::updateTilesSprite()
{
	this->graphicsData->TilesSprite->clear();
	for (int i=0;i<Tile.size();++i)
		for (int j = 0; j < Tile[0].size(); ++j)
			if (Tile[i][j] != nullptr)
				if (Tile[i][j]->SpritePtr!=nullptr)
			{
				this->graphicsData->TilesSprite->push_back(Tile[i][j]->SpritePtr);
			}
	this->equipmentData->needToUpdateTilesSpriteVec = 0;
}

void State::updateBlockades()
{
	for (int i=0;i<this->Blockade.size();++i)
		std::fill(this->Blockade[i].begin(), this->Blockade[i].end(), 0);
	for (int i = 0; i < Tile.size(); ++i)
		for (int j = 0; j < Tile[0].size(); ++j)
			if (Tile[i][j] != nullptr)
			{
				this->Blockade[i][j] = this->Tile.at(i).at(j)->blokade;
				if (this->Blockade[i][j]==1)
					this->BlockadeDimension[i][j] = (sf::Vector2f)this->Tile.at(i).at(j)->sizeOfBlockade;
			}
}

