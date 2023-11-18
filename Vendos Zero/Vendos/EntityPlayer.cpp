#include "EntityPlayer.h"

EntityPlayer::EntityPlayer(sf::Vector2f position, std::string NameOfTxt, GraphicsData *graphicsData)
	: Entity(position, NameOfTxt, graphicsData)
{
	//this->Enti = Entit;
	
	changeTexture();
}

EntityPlayer::~EntityPlayer()
{

}

void EntityPlayer::changeTexture()
{
	this->graphicsData->EntitiesSprite->back()->setTextureRect(sf::IntRect(21, 20, 40, 85));
	

	//Center of 
	getCenterOfPlayer();

	this->graphicsData->EntitiesSprite->back()->setPosition(this->centerOfGame);
}

void EntityPlayer::update(const float& dt)
{

}

void EntityPlayer::movement(const float& dt)
{

}

void EntityPlayer::getCenterOfPlayer()
{
	centerOfGame.x = this->graphicsData->window->getSize().x / 2 - 40 / 2;
	centerOfGame.y = this->graphicsData->window->getSize().y / 2 - 85 / 2;
}

sf::Vector2f EntityPlayer::Center()
{
	return centerOfGame;
}




