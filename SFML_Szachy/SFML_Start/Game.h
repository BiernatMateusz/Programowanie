#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include "Szachownica.h"
#include "PiecesMovement.h"


class Game
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;
	Szachownica* szachownica;

	


	//Initialize
	void initWindow();
	void initSzachownica();

public:
	//Variables
	sf::Vector2i MousePosition;

	//Konstruktor
	Game();
	//Destruktor
	virtual ~Game();

	//Functions
	void updateSfEvents();
	void update();
	void render();
	void run();

	
	

};

#endif 