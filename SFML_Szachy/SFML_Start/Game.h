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

#endif 