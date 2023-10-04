#ifndef GAME
#define GAME

#include <iostream>
#include "StateMenu.h"
#include "StateSpawnPlace.h"
#include <stack>
class Game
{


private:
	//variables
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
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

	//functions
	void endApp();


	//Update
	void updateSfEvents();
	void update();
	void updateDT();

	//Render
	void render();
	void run();

	

protected:


};

#endif