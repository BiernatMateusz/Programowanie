<<<<<<< HEAD
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "ChessBoard.h"


class Game
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;
	ChessBoard* chessBoard;
	sf::Vector2i MousePosition;

	//Initialize
	void initWindow();
	void initChessBoard();

public:
	//Construktor
	Game();

	//Destruktor
	virtual ~Game();

	//Functions
	void updateSfEvents();
	void update();
	void render();
	void run();

	
	

};

=======
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

>>>>>>> 62aa2c46b80bd51f4099328a85205c0098f2123f
#endif 