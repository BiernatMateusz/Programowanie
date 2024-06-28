#ifndef ENTITY_H
#define ENTITY_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "StructuresOfData.h"
#include <iostream>
#include <string>
#include <vector>

#include "item.h"

#include "Camera.h"
#include "ThrownItems.h"

class Entity
{
private:
	
protected:
	//class item;

	GraphicsData* graphicsData;

	std::vector<sf::Sprite*>* Enti{};

	sf::Vector2f centerOfGame;

	sf::RenderWindow* window;
	std::map<std::string, sf::Texture*>* TexturesMap;
	std::vector<ThrownItems*>* ItemsThrown;

	float speed{};
	float time{};
	int lastDir{};

	bool actionPossible{ 1 };

public:
	Entity(sf::Vector2f position, std::string NameOfTxt, GraphicsData* graphicsData);
	~Entity();

	void initTexture(std::string&& NameOfTxt, sf::Vector2f&& position);
	virtual void update(const float& dt, const std::map<std::string, button*>& AllKeys) = 0;
	virtual void render()=0;
	virtual void movement(const float& dt, std::vector<std::vector<bool>>& Blockade, std::vector<std::vector<sf::Vector2f>>& BlockadeDimension, float&& speed, MovementData&movData, 
		const std::map<std::string, button*>& AllKeys)=0;

	virtual void getCenterOfPlayer()=0;
	virtual sf::Vector2f Center();
	virtual void Animation(const float& dt, std::string&& direction)=0;

	void moveEntity(sf::Sprite* SpriteToMove, const float& dt, float speedX, float speedY);
	void moveEntitesWithoutExcluded(sf::Sprite* Excluded, const float& dt, float speedX, float speedY);
	bool checkIfBackGroundMoveable(std::string direction);
	bool CheckingPossibleMove(sf::Sprite* SprMovable,std::string&& direction, sf::Vector2i offsetForOrigin ,std::vector<std::vector<bool>>& blockade, std::vector<std::vector<sf::Vector2f>>& BlockadeDimension,
		const float& dt, float& speed);

	void pickUpThrownItem(); //ToDo

};

#endif 