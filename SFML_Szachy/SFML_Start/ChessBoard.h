#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Figura.h"
#include "PiecesMovement.h"

class ChessBoard
{
private:
	void initPiecesGraphics();
	void initChessBoard();
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
	

	//Construktor 
	ChessBoard();
	ChessBoard(const ChessBoard & ChessBoard);
	ChessBoard(ChessBoard&& ChessBoard);

	//Destructor
	~ChessBoard();

	//Assign operators
	ChessBoard operator=(const ChessBoard& ChessBoard);
	ChessBoard operator=(ChessBoard&& ChessBoard);


	//Functions
	void renderBoard(sf::RenderWindow *window);
	void renderPieces(sf::RenderWindow* window, sf::Vector2i mousePos);
	void rendPieces2(sf::RenderWindow* window,int posX,int posY, int WhichPiece, sf::Vector2i mousePos, bool isPieceGrabbed);
	void notGrabbed();
	
	

};

#endif 







