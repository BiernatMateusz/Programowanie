#include "EntityPlayer.h"

EntityPlayer::EntityPlayer(std::string NameOfTxt, std::vector<sf::Sprite*> *Entit)
{
	Texture = new sf::Texture;
	Sprite = new sf::Sprite;
	this->Enti = Entit;
	initTexture(NameOfTxt);
}

EntityPlayer::~EntityPlayer()
{
}

void EntityPlayer::initTexture(std::string& NameOfTxt)
{
	this->Texture->loadFromFile("Texture/" + NameOfTxt + ".png");
	this->Enti->push_back(new sf::Sprite);
	this->Enti->back()->setTexture(*this->Texture);
	this->Enti->back()->setTextureRect(sf::IntRect(0, 0, 60, 100));
}

void EntityPlayer::update(const float& dt)
{
}

void EntityPlayer::movement(const float& dt)
{
}




