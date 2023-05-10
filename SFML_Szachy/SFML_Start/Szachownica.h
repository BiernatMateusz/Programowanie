#ifndef SZACHOWNICA_H
#define SZACHOWNICA_H

#include "Figura.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class Szachownica
{
private:
	void initSzachownica();
public:
	//Variables
	std::vector < std::vector < Figura* >> Plansza;
	sf::Sprite sprite;

	//Konstruktor destruktor
	Szachownica();

	~Szachownica();

	void wyswietlObecnaSzachownice();
	void renderBoard(sf::RenderWindow *window);

};

#endif 







