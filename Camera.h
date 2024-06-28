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

public:
	//Constructors:::
	Camera(GraphicsData* graphicsData);

	//Destructor
	~Camera();

	void updateAllSpritesVec(GraphicsData* graphicsData, EquipmentData* equipmentData);
	void sortVector();

	void render(sf::RenderWindow* window);


protected:
	sf::RenderWindow* Window;


private:
	//Variables
	std::vector< sf::Sprite*> AllSprites;
	std::vector< sf::Sprite*> *AllSpritesPointer;

	sf::Sprite* Player;
	sf::Vector2f CenterOfMap;
	sf::Sprite* BackGround;

	//Functions
	void initGraphicsBasics(GraphicsData* graphicsData);

};


#endif