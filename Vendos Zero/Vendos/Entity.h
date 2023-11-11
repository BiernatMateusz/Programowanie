#ifndef ENTITY_H
#define ENTITY_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <iostream>
#include <string>
#include <vector>

class Entity
{
private:
	
protected:
	sf::Texture* Texture;
	sf::Sprite* Sprite;
	std::vector<sf::Sprite*> *Enti;
public:
	Entity() {};
	Entity(std::string NameOfTxt, std::vector<sf::Sprite*> *Entit);
	~Entity();

	virtual void initTexture(std::string& NameOfTxt);
	virtual void update(const float& dt) = 0;
	virtual void movement(const float& dt) = 0;

};

#endif 