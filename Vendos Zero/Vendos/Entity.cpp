#include "Entity.h"

Entity::Entity(sf::Vector2f position, std::string NameOfTxt, std::vector<sf::Sprite*>* Entit, std::map<std::string, sf::Texture*>* TexturesMap, sf::RenderWindow* Window)
{
	Texture = new sf::Texture;
	Sprite = new sf::Sprite;
	this->window = Window;
	this->TexturesMap = TexturesMap;
	this->Enti = Entit;
	initTexture(std::move(NameOfTxt),std::move(position));
	
}

Entity::~Entity()
{
	delete Texture;
	delete Sprite;
}

void Entity::initTexture(std::string &&NameOfTxt, sf::Vector2f &&position)
{
	this->Enti->push_back(new sf::Sprite);
	this->Enti->back()->setTexture(*this->TexturesMap->at(NameOfTxt));
	this->Enti->back()->setOrigin(20, 94);
	this->Enti->back()->setPosition(position.x, position.y);
	
	
}

sf::Vector2f Entity::Center()
{

	centerOfGame.x = this->window->getSize().x / 2;
	centerOfGame.y = this->window->getSize().y / 2;
	return centerOfGame;
}
