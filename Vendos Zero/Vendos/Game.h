#ifndef GAME
#define GAME

#include <iostream>
#include "StateMenu.h"
#include "StateSpawnPlace.h"
#include <stack>

//Aby dodawac nowe grafiki nale¿y wejœæ do Game.cpp do funkcji initTextures i dopisaæ dolejne textury


class Game
{


private:
	//variables
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;

	std::vector<sf::Texture*>GraphicsTxtVec;
	std::map<std::string, sf::Texture*>TexturesMap; //Do zrobienia

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
	void LoadNewGraphic(std::string&& name);
	

protected:


};

#endif