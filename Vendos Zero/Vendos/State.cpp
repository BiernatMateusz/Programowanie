#include "State.h"

State::State(GraphicsData* graphicsData, std::stack<State*>* Stat)
{
	this->graphicsData = graphicsData;
	this->stat = Stat;
	this->quit = false;
	this->SpritesEntiPointer = &this->SpritesEnti;

	// ---GRAPHICS SPRITES
	this->graphicsData->GraphicsSprite = &this->GraphicsSprite;
	for (auto* elem : *this->graphicsData->GraphicsSprite)
		delete elem;

	this->graphicsData->GraphicsSprite->clear();
	//

	this->entiesPointer = &this->entities;

	// ---ENTITIES SPRITES
	this->graphicsData->EntitiesSprite = &this->SpritesEnti;
	for (auto* elem : *this->graphicsData->EntitiesSprite)
		delete elem;

	this->graphicsData->EntitiesSprite->clear();
	//

	// ---TILES SPRITES
	this->graphicsData->TilesSprite = &this->TilesSprite;
	for (auto* elem : *this->graphicsData->TilesSprite)
		delete elem;

	this->graphicsData->TilesSprite->clear();
	//

}

State::~State()
{
	delete this->graphicsData->window;
	delete NewEntity;
	std::cout << "Usunalem stat\n";
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::getMousePosition()
{
	this->graphicsData->mousePosition.x = sf::Mouse::getPosition().x - this->graphicsData->window->getPosition().x;
	this->graphicsData->mousePosition.y = sf::Mouse::getPosition().y - this->graphicsData->window->getPosition().y;
}

bool State::checkExactPosition(int x,int offsetX,int y,int offsetY)
{
		return (this->graphicsData->mousePosition.x > x && this->graphicsData->mousePosition.x < offsetX && this->graphicsData->mousePosition.y>y && this->graphicsData->mousePosition.y < offsetY);
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit = true;
	}
}

void State::LoadBackground(sf::Vector2f&& position, std::string&& NameOfTxt)
{
	this->graphicsData->backGround = new sf::Sprite;
	this->graphicsData->GraphicsSprite->push_back(new sf::Sprite);
	this->graphicsData->GraphicsSprite->back()->setTexture(*this->graphicsData->TexturesMap->at(NameOfTxt));

	this->graphicsData->backGround = graphicsData->GraphicsSprite->back();

	//Setting origins
	if (NameOfTxt == "Mapka")
		this->graphicsData->GraphicsSprite->back()->setOrigin(0, this->graphicsData->GraphicsSprite->back()->getGlobalBounds().height);

	this->graphicsData->GraphicsSprite->back()->setPosition(position.x, position.y);

}

void State::initTile(sf::Vector2i&& position2i, std::string&& NameOfTxt)
{
	int x = position2i.x/44;
	int y = position2i.y/44 - 1;
	this->Tile[x][y] = new TilesOnMap;
	this->Tile[x][y]->SpritePtr = new sf::Sprite;
	this->Tile[x][y]->SpritePtr->setTexture(*this->graphicsData->TextureDataMap->at(NameOfTxt)->texture);
	this->Tile[x][y]->SpritePtr->setOrigin(this->graphicsData->TextureDataMap->at(NameOfTxt)->origin.x, this->Tile[x][y]->SpritePtr->getGlobalBounds().height + this->graphicsData->TextureDataMap->at(NameOfTxt)->origin.y);
	this->Tile[x][y]->SpritePtr->setPosition(position2i.x,position2i.y+this->graphicsData->TextureDataMap->at(NameOfTxt)->offsetForPositon);

	this->Tile[x][y]->blokade = this->graphicsData->TextureDataMap->at(NameOfTxt)->blockade;

	if (Tile[x][y]->blokade == 1)
		Tile[x][y]->sizeOfBlockade = this->graphicsData->TextureDataMap->at(NameOfTxt)->blockadeSize;

	//this->Tile[x][y]->ticksToChangeItself = XXX;		***ToDo*** add to function
	//this->Tile[x][y]->typeOfTile = XXX;				***ToDo*** add to function

}

void State::updateTilesSprite()
{
	this->graphicsData->TilesSprite->clear();
	for (int i=0;i<Tile.size();++i)
		for (int j = 0; j < Tile[0].size(); ++j)
			if (Tile[i][j] != nullptr)
			{
				this->graphicsData->TilesSprite->push_back(Tile[i][j]->SpritePtr);
			}
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

