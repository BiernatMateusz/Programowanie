#include "ChessBoard.h"


ChessBoard::ChessBoard()
{
	initChessBoard();
	initPiecesGraphics();
	initPiecesMov();
	initVariables();
	
}





ChessBoard::ChessBoard(const ChessBoard& ChessBoard)
{
	Plansza = ChessBoard.Plansza;
	HoldedPiece = new Figura;
	*HoldedPiece = *ChessBoard.HoldedPiece;
	PiecesGraphics = ChessBoard.PiecesGraphics;
	sprite = ChessBoard.sprite;
	piece = ChessBoard.piece;
	piecesMov = new PiecesMovement;
	*piecesMov = *ChessBoard.piecesMov;
	OneOfPiecesGrabbed = ChessBoard.OneOfPiecesGrabbed;
	WhichColorTurn = ChessBoard.WhichColorTurn;
	EnPaisPawn = ChessBoard.EnPaisPawn;
}

ChessBoard::ChessBoard(ChessBoard&& ChessBoard)
{
	Plansza = ChessBoard.Plansza;
	HoldedPiece = ChessBoard.HoldedPiece;
	PiecesGraphics = ChessBoard.PiecesGraphics;
	sprite = ChessBoard.sprite;
	piece = ChessBoard.piece;
	piecesMov = ChessBoard.piecesMov;
	OneOfPiecesGrabbed = ChessBoard.OneOfPiecesGrabbed;
	WhichColorTurn = ChessBoard.WhichColorTurn;
	EnPaisPawn = ChessBoard.EnPaisPawn;
	ChessBoard.HoldedPiece = nullptr;
	ChessBoard.piecesMov = nullptr;
}



ChessBoard::~ChessBoard()
{
	delete this->piecesMov;
	delete this->HoldedPiece;
	
}

ChessBoard ChessBoard::operator=(const ChessBoard& ChessBoard)
{
	if (&ChessBoard != this)
	{
		delete HoldedPiece;
		delete piecesMov;

		Plansza = ChessBoard.Plansza;
		HoldedPiece = new Figura;
		*HoldedPiece = *ChessBoard.HoldedPiece;
		PiecesGraphics = ChessBoard.PiecesGraphics;
		sprite = ChessBoard.sprite;
		piece = ChessBoard.piece;
		piecesMov = new PiecesMovement;
		*piecesMov = *ChessBoard.piecesMov;
		OneOfPiecesGrabbed = ChessBoard.OneOfPiecesGrabbed;
		WhichColorTurn = ChessBoard.WhichColorTurn;
		EnPaisPawn = ChessBoard.EnPaisPawn;
	}
	return *this;
}

ChessBoard ChessBoard::operator=(ChessBoard&& ChessBoard)
{
	if (&ChessBoard != this)
	{
		delete HoldedPiece;
		delete piecesMov;
		
		Plansza = ChessBoard.Plansza;
		HoldedPiece = ChessBoard.HoldedPiece;
		PiecesGraphics = ChessBoard.PiecesGraphics;
		sprite = ChessBoard.sprite;
		piece = ChessBoard.piece;
		piecesMov = ChessBoard.piecesMov;
		OneOfPiecesGrabbed = ChessBoard.OneOfPiecesGrabbed;
		WhichColorTurn = ChessBoard.WhichColorTurn;
		EnPaisPawn = ChessBoard.EnPaisPawn;
		ChessBoard.HoldedPiece = nullptr;
		ChessBoard.piecesMov = nullptr;
	}
	return *this;
}




void ChessBoard::initChessBoard()
{
	this->Plansza.resize(8);
	std::string FigureNames = "WSGHKGSW", charToStr;
	bool white{ 0 }, black{ 1 };

	//[x][y]

	for (int BoardHorizontal = 0; BoardHorizontal < 8; BoardHorizontal++)
	{
		this->Plansza[BoardHorizontal].resize(8);
		this->Plansza[BoardHorizontal][0] = new Figura{ charToStr = (FigureNames[BoardHorizontal]),white,false,BoardHorizontal,0 }; //White pieces
		this->Plansza[BoardHorizontal][1] = new Figura{ "P",white,false,BoardHorizontal,0 };
		this->Plansza[BoardHorizontal][7] = new Figura{ charToStr = (FigureNames[BoardHorizontal]),black,false,BoardHorizontal,7 }; //Black pieces
		this->Plansza[BoardHorizontal][6] = new Figura{ "P",black,false,BoardHorizontal,6 };
		for (int BoardVertical = 2; BoardVertical < 6; ++BoardVertical)
			this->Plansza[BoardHorizontal][BoardVertical] = nullptr;
	}

}

void ChessBoard::initPiecesGraphics()
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

void ChessBoard::renderBoard(sf::RenderWindow *window)
{
	sf::Texture board;
	board.loadFromFile("Texture/Board.png");
	this->sprite.setTexture(board);
	this->sprite.setScale(800.0f/1166.0f, 800.0f / 1168.0f);
	window->draw(this->sprite);

}

void ChessBoard::renderPieces(sf::RenderWindow* window, sf::Vector2i mousePos)
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

void ChessBoard::rendPieces2(sf::RenderWindow* window,int posX,int posY, int WhichPiece, sf::Vector2i mousePos, bool isPieceGrabbed)
{
	if (isPieceGrabbed==0)
		this->PiecesGraphics[WhichPiece].setPosition(posX * 100, (-posY * 100) + 700);
	else 
		this->PiecesGraphics[WhichPiece].setPosition(mousePos.x-58, mousePos.y-54);
	window->draw(this->PiecesGraphics[WhichPiece]);
}



void ChessBoard::initPiecesMov()
{
	this->piecesMov = new PiecesMovement;
}

void ChessBoard::initVariables()
{
	this->HoldedPiece = nullptr;
	this->OneOfPiecesGrabbed = 0 ;
	this->WhichColorTurn = 1 ;
}

void ChessBoard::notGrabbed()
{
	for (int i=0; i<8;++i)
		for (int j = 0; j < 8; ++j)
			if (this->Plansza[i][j]!=nullptr)
		{
			this->Plansza[i][j]->Grabbed = 0;
		}
	this->OneOfPiecesGrabbed = 0;
}

Figura*& ChessBoard::HoldedPieceFF()
{
	return this->HoldedPiece;
}

PiecesMovement* ChessBoard::piecesMove()
{
	return this->piecesMov;
}

bool& ChessBoard::OneOfPiecesGrabbedF()
{
	return this->OneOfPiecesGrabbed;
}

bool& ChessBoard::WhichColorTurnF()
{
	return this->WhichColorTurn;
}






