#include "Szachownica.h"




Szachownica::Szachownica()
{
	initSzachownica();

	wyswietlObecnaSzachownice();
}

Szachownica::~Szachownica()
{
	
}




void Szachownica::initSzachownica()
{
	this->Plansza.resize(8);
	for (int i = 0; i < 8; i++)
		this->Plansza[i].resize(8);

	//[x][y]
	//Bialy

	this->Plansza[0][0] = new Figura{ "W",0 };
	this->Plansza[1][0] = new Figura{ "S",0 };
	this->Plansza[2][0] = new Figura{ "G",0 };
	this->Plansza[3][0] = new Figura{ "H",0 };
	this->Plansza[4][0] = new Figura{ "K",0 };
	this->Plansza[5][0] = new Figura{ "G",0 };
	this->Plansza[6][0] = new Figura{ "S",0 };
	this->Plansza[7][0] = new Figura{ "W",0 };

	for (int i = 0; i < 8; ++i)
		this->Plansza[i][1] = new Figura{ "P",0 };

	//Czarny
	this->Plansza[0][7] = new Figura{ "W",1 };
	this->Plansza[1][7] = new Figura{ "S",1 };
	this->Plansza[2][7] = new Figura{ "G",1 };
	this->Plansza[3][7] = new Figura{ "H",1 };
	this->Plansza[4][7] = new Figura{ "K",1 };
	this->Plansza[5][7] = new Figura{ "G",1 };
	this->Plansza[6][7] = new Figura{ "S",1 };
	this->Plansza[7][7] = new Figura{ "W",1 };

	for (int i = 0; i < 8; ++i)
		this->Plansza[i][6] = new Figura{ "P",1 };


	for (int i = 0; i < 8; ++i)
		for (int j = 2; j < 6; ++j)
			this->Plansza[i][j] = nullptr;

	

}

void Szachownica::wyswietlObecnaSzachownice()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (Plansza[j][i] != nullptr)
			{
				std::cout << Plansza[j][i]->nazwaFigury() << " ";
			}
			else
			{
				std::cout << "- ";
			}
		}
		std::cout << "\n";
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


////////////////////////////////////////////

//8  CZ_W CZ_S CZ_G CZ_H CZ_K CZ_G CZ_S CZ_W
//7  CZ_P CZ_P CZ_P CZ_P CZ_P CZ_P CZ_P CZ_P 
//6  -    -    -    -    -    -    -    -    
//5  -    -    -    -    -    -    -    -    
//4  -    -    -    -    -    -    -    -    
//3  -    -    -    -    -    -    -    -    
//2  B_P  B_P  B_P  B_P  B_P  B_P  B_P  B_P
//1  B_W  B_S  B_G  B_H  B_K  B_G  B_S  B_W

////////////////////////////////////////////

