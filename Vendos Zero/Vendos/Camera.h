#ifndef CAMERA_H
#define CAMERA_H

//DOPISAC FUNKCJE KTORA PRZY KAZDYM NOWYM ELEMENCIE NA NOWO SORTUJE, SORTUJE PRZY KAZDYM RUCHU 
//ZMIANA RENDERINGU => mapa zawsze musi sie renderowac

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "StructuresOfData.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

class Camera
{
private:
	//Variables
	std::vector< sf::Sprite*> AllSprites;
	std::vector< sf::Sprite*> *AllSpritesPointer;

	sf::Sprite* Player;
	sf::Vector2f CenterOfMap;
	sf::Sprite* BackGround;

	float time{};
	int lastDir{};

	//Functions
	bool checkIfBackGroundMoveable(std::string direction);
	void moveAllObjects(sf::Sprite * Excluded, const float& dt, float speedX, float speedY);
	void movePlayer(const float& dt, float speedX, float speedY);
	bool CheckingPossibleMove(std::string&& direction, std::vector<std::vector<bool>>& blockade, std::vector<std::vector<sf::Vector2f>>& BlockadeDimension, const float& dt, float & speed);
	void PlayerAnimation(const float& dt, std::string&& direction);



protected:
	sf::RenderWindow* Window;
public:
	Camera(std::vector<sf::Sprite*>* GraphicsSpr,sf::RenderWindow* window);
	Camera(std::vector<sf::Sprite*>* GraphicsSpr, std::vector<sf::Sprite*>* EntitySpr, sf::RenderWindow* window);

	~Camera();

	void sortVector();

	bool movementAll(const float& dt,std::vector<std::vector<bool>>&Blockade, std::vector<std::vector<sf::Vector2f>>& BlockadeDimension, float&& speed);

	void render(sf::RenderWindow* window);
};


#endif