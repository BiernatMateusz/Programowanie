#ifndef PIECESMOVEMENT_H
#define PIECESMOVEMENT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Figura.h"


class PiecesMovement
{
private:
	//Variables
	sf::Vector2i position;
	
public:
	
	//Konstruktor destruktor
	PiecesMovement();
	virtual ~PiecesMovement();
	std::vector<bool(PiecesMovement::*)(std::vector<std::vector<Figura*>>& Plansza, Figura*& HoldedPiece, sf::Vector2i mousePos, Figura& EnPaisPawn)>EveryPieceMovement;

	//Functions
	sf::Vector2i getMousePos1(sf::RenderWindow* window);
	void GrabbingPiece(std::vector<std::vector<Figura*>>board,sf::Vector2i MousePos, bool &GrabbedPiece, Figura*& HoldedPiece);
	void newPositionOfPiece(sf::Vector2i mousePos, std::vector < std::vector < Figura* >>& Plansza, Figura*& HoldedPiece, bool &WhichColorTurn, Figura& EnPaiPawn);
	bool pawnMove(std::vector < std::vector < Figura* >> &Plansza, Figura* &HoldedPiece, sf::Vector2i mousePos, Figura& EnPaisPawn);
	bool kingMove(std::vector < std::vector < Figura* >> &Plansza, Figura* &HoldedPiece, sf::Vector2i mousePos, Figura& EnPaisPawn);
	bool queenMove(std::vector < std::vector < Figura* >> &Plansza, Figura* &HoldedPiece, sf::Vector2i mousePos, Figura& EnPaisPawn);
	bool knightMove(std::vector < std::vector < Figura* >> &Plansza, Figura* &HoldedPiece, sf::Vector2i mousePos, Figura& EnPaisPawn);
	bool bishopMove(std::vector < std::vector < Figura* >> &Plansza, Figura* &HoldedPiece, sf::Vector2i mousePos, Figura& EnPaisPawn);
	bool rookMove(std::vector < std::vector < Figura* >> &Plansza, Figura* &HoldedPiece, sf::Vector2i mousePos, Figura& EnPaisPawn);

	void makeVector2(); //VECTOR OF FUNCTIONS TO CHECK FOR AVAILABLE SQARES

	bool LookingForCheck(std::vector < std::vector < Figura* >>& Plansza, bool& WhichColorTurn, Figura& EnPaiPawn);

};

#endif 