#ifndef GAME
#define GAME

#include <iostream>
#include "StateMenu.h"
#include "StateSpawnPlace.h"
#include <stack>
#include "button.h"

//To add new textures u have to go to: ==== initTextures ==== and add new textures ---- game.cpp


class Game
{

public:
	//Constructors
	Game();
	//Destructor
	virtual ~Game();

	//Update and render functions
	void run();
	void updateSfEvents();
	void update();
	void updateDT();
	void render();
	void endApp();

	//Init functions
	void initStates();
	void initTextures();
	void initGraphicsData();
	

	//Graphics functions 
	void LoadNewGraphic(std::string&& name, int itemID);
	void LoadNewGraphic(std::string&& name, sf::Vector2i blockadeSize, sf::Vector2i origin, float offsetForPositonY, bool blockade, int typeOfTile, int itemID);


protected:


private:
	//variables
	sf::RenderWindow* window;
	int WindowLenght{ 1200 }, WindowHight{ 1000 };
	sf::Event sfEvent;

	sf::Clock dtClock;
	std::map<std::string, button*>AllKeys;

	//Graphics data structure
	GraphicsData* graphicsData;

	//Time
	float dt;

	//States
	std::stack<State*>states;

	//init
	void initializeWindow();
	void initAllKeys();

};

#endif