#ifndef SZACHOWNICA_H
#define SZACHOWNICA_H

#include "Figura.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "PiecesMovement.h"

class Szachownica
{
private:
	void initPiecesGraphics();
	void initSzachownica();
	void initPiecesMov();
	enum WhichPiece{CZK,CZH,CZW,CZG,CZS,CZP,BK,BH,BW,BG,BS,BP};

public:
	//Variables
	std::vector < std::vector < Figura* >> Plansza;
	Figura* HoldedPiece;
	std::vector<sf::Sprite>PiecesGraphics;
	sf::Sprite sprite;
	sf::Texture piece;
	PiecesMovement* piecesMov;
	bool OneOfPiecesGrabbed = { 0 };
	bool WhichColorTurn = { 1 };
	Figura EnPaisPawn{"EnPaisPawn",0,0,0,0};
	

	//Konstruktor destruktor
	Szachownica();

	~Szachownica();

	
	void renderBoard(sf::RenderWindow *window);
	void renderPieces(sf::RenderWindow* window, sf::Vector2i mousePos);
	void rendPieces2(sf::RenderWindow* window,int posX,int posY, int WhichPiece, sf::Vector2i mousePos, bool isPieceGrabbed);
	void notGrabbed();
	
	

};

#endif 







