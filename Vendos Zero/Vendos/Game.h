#ifndef GAME
#define GAME

#include <iostream>
#include "StateMenu.h"
#include "StateSpawnPlace.h"
#include <stack>

//To add new textures u have to go to: ==== initTextures ==== and add new textures ---- game.cpp


class Game
{


private:
	//variables
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;

	//GRAPHICS THINGS
	std::vector<sf::Texture*>GraphicsTxtVec;
	std::vector<sf::Texture*>*GraphicsTxtVecPtr=&GraphicsTxtVec;
	std::map<std::string, sf::Texture*>TexturesMap;
	std::map<std::string, sf::Texture*>*TexturesMapPtr=&TexturesMap;

	//Map with all data about graphics
	std::map<std::string, TextureData*> TextureDataMap;

	
	GraphicsData* graphicsData;


	float dt;


	std::stack<State*>states;

	int WindowLenght{ 1200 }, WindowHight{ 1000 };

	//init
	void initializeWindow();
public:
	//Constructors
	Game();
	//Destructor
	virtual ~Game();

	//Init
	void initStates();
	void initTextures();
	void initGraphicsData();

	//functions
	void endApp();


	//Update
	void updateSfEvents();
	void update();
	void updateDT();

	//Render
	void render();
	void run();

	//Additional functions
	void LoadNewGraphic(std::string&& name); //to delete
	void LoadNewGraphic(std::string&& name, sf::Vector2i blockadeSize, sf::Vector2i origin, float offsetForPositon, bool blockade);
	

protected:


};

#endif