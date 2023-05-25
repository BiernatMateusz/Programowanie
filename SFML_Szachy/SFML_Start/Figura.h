#ifndef FIGURA_H
#define FIGURA_H

#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Figura
{
private:

	
	bool kolor;				//0 biale //1 czarne
	
	sf::Sprite spritePiece;
public:
	//Variables 
	std::string Nazwa;		//W //S //G //H //K //P
	bool Grabbed;
	int posX;
	int posY;
	bool moved;

	//Used only in EnPais
	bool WhiteCheck = { 0 };
	bool BlackCheck = { 0 };

	//Konstruktor //Destruktor
	Figura(std::string Nazwa, bool kolor, bool grabbed, int posX, int posY);
	Figura();
	virtual ~Figura();

	//Functions
	std::string nazwaFigury();
	bool kolorGet();
	void PieceGrabbed(bool grabbed);
	bool PieceGrab();
	int numberOfPiece();
};

#endif