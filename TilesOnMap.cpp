#include "TilesOnMap.h"

TilesOnMap::TilesOnMap(GraphicsData* graphicsData)
{
	this->graphicsData = graphicsData;
	this->SpritePtr = nullptr;
	this->typeOfTile = 7; //empty blockade
	this->blokade = 1;
	this->sizeOfBlockade = { 40,40 };
	
}

TilesOnMap::TilesOnMap(sf::Vector2i position2i, std::string NameOfTxt, GraphicsData* graphicsData)
{
	this->graphicsData = graphicsData;
	this->SpritePtr = new sf::Sprite;
	this->SpritePtr->setTexture(*this->graphicsData->TextureDataMap->at(NameOfTxt)->texture);
	this->SpritePtr->setOrigin(this->graphicsData->TextureDataMap->at(NameOfTxt)->origin.x, this->SpritePtr->getGlobalBounds().height + this->graphicsData->TextureDataMap->at(NameOfTxt)->origin.y);
	this->SpritePtr->setPosition((float)position2i.x * 44 + this->graphicsData->backGround->getPosition().x, ((float)position2i.y + 1) * 44 + this->graphicsData->TextureDataMap->at(NameOfTxt)->offsetForPositonY - (this->graphicsData->backGround->getGlobalBounds().height - this->graphicsData->backGround->getPosition().y));

	this->blokade = this->graphicsData->TextureDataMap->at(NameOfTxt)->blockade;

	if (this->blokade == 1)
		this->sizeOfBlockade = this->graphicsData->TextureDataMap->at(NameOfTxt)->blockadeSize;

	this->typeOfTile = this->graphicsData->TextureDataMap->at(NameOfTxt)->typeOfTile;

}

TilesOnMap::~TilesOnMap()
{
	delete this->SpritePtr;
	if (this->chest != nullptr)
		delete this->chest;

}
