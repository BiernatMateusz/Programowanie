#include "EntityPlayer.h"

EntityPlayer::EntityPlayer(sf::Vector2f position, std::string NameOfTxt, std::vector<sf::Sprite*>* Entit, std::map<std::string, sf::Texture*>* TexturesMap, sf::RenderWindow* Window)
	: Entity(position, NameOfTxt, Entit,TexturesMap, Window)
{
	this->Enti = Entit;

	changeTexture();
}

EntityPlayer::~EntityPlayer()
{

}

void EntityPlayer::changeTexture()
{
	this->Enti->back()->setTextureRect(sf::IntRect(0, 0, 60, 100));
	this->Enti->back()->setScale(0.85, 0.85);

	//Center of 
	getCenterOfPlayer();

	this->Enti->back()->setPosition(this->centerOfGame);

	std::cout << this->Enti->back()->getGlobalBounds().width << "\n";
	std::cout << this->Enti->back()->getGlobalBounds().height << "\n";
}

void EntityPlayer::update(const float& dt)
{
}

void EntityPlayer::movement(const float& dt)
{

}

void EntityPlayer::getCenterOfPlayer()
{
	centerOfGame.x = this->window->getSize().x / 2 - 60*0.85 / 2;
	centerOfGame.y = this->window->getSize().y / 2 - 100*0.85 / 2;
}

sf::Vector2f EntityPlayer::Center()
{
	return centerOfGame;
}




