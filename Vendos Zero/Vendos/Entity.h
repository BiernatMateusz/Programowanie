#ifndef ENTITY_H
#define ENTITY_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "StructuresOfData.h"
#include <iostream>
#include <string>
#include <vector>

class Entity
{
private:
	
protected:
	sf::Texture* Texture{};
	sf::Sprite* Sprite{};
	std::vector<sf::Sprite*>* Enti{};

	sf::Vector2f centerOfGame;

	sf::RenderWindow* window;
	std::map<std::string, sf::Texture*>* TexturesMap;

	float speed{};
	
public:
	Entity(sf::Vector2f position, std::string NameOfTxt, std::vector<sf::Sprite*>* Entit, std::map<std::string, sf::Texture*>* TexturesMap, sf::RenderWindow* Window);
	~Entity();

	void initTexture(std::string&& NameOfTxt, sf::Vector2f&& position);
	virtual void update(const float& dt) = 0;
	virtual void movement(const float& dt) = 0;
	virtual void getCenterOfPlayer()=0;
	virtual sf::Vector2f Center();

};

#endif 