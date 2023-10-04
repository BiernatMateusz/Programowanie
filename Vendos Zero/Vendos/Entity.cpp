#include "Entity.h"

Entity::Entity(std::string NameOfTxt, std::vector<sf::Sprite*> *Entit)
{
	Texture = new sf::Texture;
	Sprite = new sf::Sprite;
	this->Enti = Entit;
	initTexture(NameOfTxt);

	
}

Entity::~Entity()
{
	delete Texture;
	delete Sprite;
}

void Entity::initTexture(std::string &NameOfTxt)
{
	this->Texture->loadFromFile("Texture/" + NameOfTxt + ".png");
	this->Enti->push_back(new sf::Sprite);
	this->Enti->back()->setTexture(*this->Texture);
	std::cout << "XD\n";
	
}
