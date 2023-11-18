#include "Entity.h"

Entity::Entity(sf::Vector2f position, std::string NameOfTxt, GraphicsData* graphicsData)
{
	
	this->graphicsData = graphicsData;
	Texture = new sf::Texture;
	Sprite = new sf::Sprite;
	
	initTexture(std::move(NameOfTxt),std::move(position));
	
}

Entity::~Entity()
{
	delete Texture;
	delete Sprite;
}

void Entity::initTexture(std::string &&NameOfTxt, sf::Vector2f &&position)
{
	this->graphicsData->EntitiesSprite->push_back(new sf::Sprite);
	this->graphicsData->EntitiesSprite->back()->setTexture(*this->graphicsData->TexturesMap->at(NameOfTxt));
	this->graphicsData->EntitiesSprite->back()->setOrigin(18, 76);
	this->graphicsData->EntitiesSprite->back()->setPosition(position.x, position.y);
}

sf::Vector2f Entity::Center()
{

	centerOfGame.x = this->graphicsData->window->getSize().x / 2;
	centerOfGame.y = this->graphicsData->window->getSize().y / 2;
	return centerOfGame;
}
