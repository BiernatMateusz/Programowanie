#ifndef OBJECTS
#define OBEJCTS

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

class Objects
{
public:
	//constructor
	Objects() {};

	//destructor
	virtual ~Objects();

	//functions
	virtual void InitializeTextureF(std::string txtName, sf::Vector2f position, float scale) = 0;
	virtual void DrawingObjectF(sf::RenderWindow* window, float& PlayerTime) = 0;
	virtual void MovingObjectF(float& dt, sf::Vector2f position) = 0;

private:


protected:
	//variables
	sf::Vector2f Position;
	sf::Sprite Sprite_Object;
	sf::Texture Txt_Object;

};

#endif 