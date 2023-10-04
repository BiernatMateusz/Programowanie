#ifndef CAMERA_H
#define CAMERA_H

//DOPISAC FUNKCJE KTORA PRZY KAZDYM NOWYM ELEMENCIE NA NOWO SORTUJE, SORTUJE PRZY KAZDYM RUCHU 
//ZMIANA RENDERINGU => mapa zawsze musi sie renderowac

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Camera
{
private:
	std::vector< sf::Sprite*> AllSprites;
	std::vector< sf::Sprite*> *AllSpritesPointer;
	sf::Sprite a, b;
protected:
	sf::RenderWindow* Window;
public:
	Camera(std::vector<sf::Sprite*>* GraphicsSpr,sf::RenderWindow* window);
	Camera(std::vector<sf::Sprite*>* GraphicsSpr, std::vector<sf::Sprite*>* EntitySpr, sf::RenderWindow* window);

	~Camera();

	void sortVector(std::vector<sf::Sprite*>* &AllSpr);

	void render(sf::RenderWindow* window);
};


#endif