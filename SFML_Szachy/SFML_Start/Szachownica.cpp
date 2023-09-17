#include "Szachownica.h"


Szachownica::Szachownica()
{
	initSzachownica();
	initPiecesGraphics();
	initPiecesMov();
	this->HoldedPiece = nullptr;
}

Szachownica::~Szachownica()
{
	delete this->piecesMov;
}




void Szachownica::initSzachownica()
{
	this->Plansza.resize(8);
	for (int i = 0; i < 8; i++)
		this->Plansza[i].resize(8);

	//[x][y]
	//Bialy

	this->Plansza[0][0] = new Figura{ "W",0,false,0,0 };
	this->Plansza[1][0] = new Figura{ "S",0,false,1,0 };
	this->Plansza[2][0] = new Figura{ "G",0,false,2,0 };
	this->Plansza[3][0] = new Figura{ "H",0,false,3,0 };
	this->Plansza[4][0] = new Figura{ "K",0,false,4,0 };
	this->Plansza[5][0] = new Figura{ "G",0,false,5,0 };
	this->Plansza[6][0] = new Figura{ "S",0,false,6,0 };
	this->Plansza[7][0] = new Figura{ "W",0,false,7,0 };

	for (int i = 0; i < 8; ++i)
		this->Plansza[i][1] = new Figura{ "P",0,false,0,0 };

	//Czarny
	this->Plansza[0][7] = new Figura{ "W",1,false,0,7 };
	this->Plansza[1][7] = new Figura{ "S",1,false,1,7 };
	this->Plansza[2][7] = new Figura{ "G",1,false,2,7 };
	this->Plansza[3][7] = new Figura{ "H",1,false,3,7 };
	this->Plansza[4][7] = new Figura{ "K",1,false,4,7 };
	this->Plansza[5][7] = new Figura{ "G",1,false,5,7 };
	this->Plansza[6][7] = new Figura{ "S",1,false,6,7 };
	this->Plansza[7][7] = new Figura{ "W",1,false,7,7 };

	for (int i = 0; i < 8; ++i)
		this->Plansza[i][6] = new Figura{ "P",1,false,i,6 };


	for (int i = 0; i < 8; ++i)
		for (int j = 2; j < 6; ++j)
			this->Plansza[i][j] = nullptr;

	

}

void Szachownica::initPiecesGraphics()
{
	static bool PiecesGraphicsNotEmpty = false;
	if (PiecesGraphicsNotEmpty == false)
	{
		sf::Sprite sprPiece;
		this->piece.loadFromFile("Texture/Pieces.png");
		sprPiece.setTexture(this->piece);
		
		for (int vertical = 0; vertical < 2; ++vertical)
			for (int horizontal=0; horizontal <6;++horizontal)
			{
			sprPiece.setTextureRect(sf::IntRect((horizontal *168)+20, (vertical *144)+20, 140, 140));
			this->PiecesGraphics.push_back(sprPiece);
			}

		PiecesGraphicsNotEmpty = true;
	}
}

void Szachownica::renderBoard(sf::RenderWindow *window)
{
	sf::Texture board;
	board.loadFromFile("Texture/Board.png");
	this->sprite.setTexture(board);
	this->sprite.setScale(800.0f/1166.0f, 800.0f / 1168.0f);
	window->draw(this->sprite);

}

void Szachownica::renderPieces(sf::RenderWindow* window, sf::Vector2i mousePos)
{
	for (int posY= 0; posY < 8; ++posY)
	{
		for (int posX = 0; posX < 8; ++posX)
		{
			if (Plansza[posX][posY] != nullptr)
			{
				if (Plansza[posX][posY]->nazwaFigury() == "K" && Plansza[posX][posY]->kolorGet() == 0) //Bialy kr鏊
					rendPieces2(window, posX,posY,WhichPiece::BK,mousePos, this->Plansza[posX][posY]->PieceGrab());
				
				else if (Plansza[posX][posY]->nazwaFigury() == "H" && Plansza[posX][posY]->kolorGet() == 0) //Bia造 hetman
					rendPieces2(window, posX, posY, WhichPiece::BH, mousePos, this->Plansza[posX][posY]->PieceGrab());
				
				else if (Plansza[posX][posY]->nazwaFigury() == "W" && Plansza[posX][posY]->kolorGet() == 0) //bia造 wie瘸
					rendPieces2(window, posX, posY, WhichPiece::BW, mousePos, this->Plansza[posX][posY]->PieceGrab());
				
				else if (Plansza[posX][posY]->nazwaFigury() == "G" && Plansza[posX][posY]->kolorGet() == 0) //bia造 goniec
					rendPieces2(window, posX, posY, WhichPiece::BG, mousePos, this->Plansza[posX][posY]->PieceGrab());
				
				else if (Plansza[posX][posY]->nazwaFigury() == "S" && Plansza[posX][posY]->kolorGet() == 0) //bia造 kon
					rendPieces2(window, posX, posY, WhichPiece::BS, mousePos, this->Plansza[posX][posY]->PieceGrab());
				
				else if (Plansza[posX][posY]->nazwaFigury() == "P" && Plansza[posX][posY]->kolorGet() == 0) //bialy pion
					rendPieces2(window, posX, posY, WhichPiece::BP, mousePos, this->Plansza[posX][posY]->PieceGrab());
				
				else if (Plansza[posX][posY]->nazwaFigury() == "K" && Plansza[posX][posY]->kolorGet() == 1) //czarny kr鏊
					rendPieces2(window, posX, posY, WhichPiece::CZK, mousePos, this->Plansza[posX][posY]->PieceGrab());
				
				else if (Plansza[posX][posY]->nazwaFigury() == "H" && Plansza[posX][posY]->kolorGet() == 1) //czarny hetman
					rendPieces2(window, posX, posY, WhichPiece::CZH, mousePos, this->Plansza[posX][posY]->PieceGrab());
				
				else if (Plansza[posX][posY]->nazwaFigury() == "W" && Plansza[posX][posY]->kolorGet() == 1) //czarny wie瘸
					rendPieces2(window, posX, posY, WhichPiece::CZW, mousePos, this->Plansza[posX][posY]->PieceGrab());
				
				else if (Plansza[posX][posY]->nazwaFigury() == "G" && Plansza[posX][posY]->kolorGet() == 1) //czarny goniec
					rendPieces2(window, posX, posY, WhichPiece::CZG, mousePos, this->Plansza[posX][posY]->PieceGrab());
				
				else if (Plansza[posX][posY]->nazwaFigury() == "S" && Plansza[posX][posY]->kolorGet() == 1) //czarny kon
					rendPieces2(window, posX, posY, WhichPiece::CZS, mousePos, this->Plansza[posX][posY]->PieceGrab());
				
				else if (Plansza[posX][posY]->nazwaFigury() == "P" && Plansza[posX][posY]->kolorGet() == 1) //czarny pion
					rendPieces2(window, posX, posY, WhichPiece::CZP, mousePos, this->Plansza[posX][posY]->PieceGrab());
			}
		}
	}
}

void Szachownica::rendPieces2(sf::RenderWindow* window,int posX,int posY, int WhichPiece, sf::Vector2i mousePos, bool isPieceGrabbed)
{
	if (isPieceGrabbed==0)
		this->PiecesGraphics[WhichPiece].setPosition(posX * 100, (-posY * 100) + 700);
	else 
		this->PiecesGraphics[WhichPiece].setPosition(mousePos.x-58, mousePos.y-54);
	window->draw(this->PiecesGraphics[WhichPiece]);
}



void Szachownica::initPiecesMov()
{
	this->piecesMov = new PiecesMovement;
}

void Szachownica::notGrabbed()
{
	for (int i=0; i<8;++i)
		for (int j = 0; j < 8; ++j)
			if (this->Plansza[i][j]!=nullptr)
		{
			this->Plansza[i][j]->Grabbed = 0;
		}
}




