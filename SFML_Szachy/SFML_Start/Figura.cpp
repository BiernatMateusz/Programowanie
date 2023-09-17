<<<<<<< HEAD
#include "Figura.h"

//Constructor destructor
Figura::Figura(std::string Nazwa, bool kolor, bool grabbed,int posX,int posY)
{

	this->Nazwa = Nazwa;
	this->kolor = kolor;
	this->Grabbed = grabbed;
	this->posX = posX;
	this->posY = posY;

	moved = 0;
}

Figura::Figura()
{
	
}

Figura::~Figura()
{

}




//Functions
std::string Figura::nazwaFigury()
{
	return this->Nazwa;
}

bool Figura::kolorGet()
{
	return this->kolor;
}

void Figura::PieceGrabbed(bool grabbed)
{
	this->Grabbed = grabbed;
}

bool Figura::PieceGrab()
{
	return Grabbed;
}

int Figura::numberOfPiece()
{
	int numberOfFigure;
		if (this->Nazwa == "P")
			numberOfFigure = 0;
		if (this->Nazwa == "K")
			numberOfFigure = 1;
		if (this->Nazwa == "H")
			numberOfFigure = 2;
		if (this->Nazwa == "S")
			numberOfFigure = 3;
		if (this->Nazwa == "G")
			numberOfFigure = 4;
		if (this->Nazwa == "W")
			numberOfFigure = 5;

	return numberOfFigure;
}


=======
#include "Figura.h"

//Constructor destructor
Figura::Figura(std::string Nazwa, bool kolor, bool grabbed,int posX,int posY)
{

	this->Nazwa = Nazwa;
	this->kolor = kolor;
	this->Grabbed = grabbed;
	this->posX = posX;
	this->posY = posY;

	moved = 0;
}

Figura::Figura()
{

}

Figura::~Figura()
{

}




//Functions
std::string Figura::nazwaFigury()
{
	return this->Nazwa;
}

bool Figura::kolorGet()
{
	return this->kolor;
}

void Figura::PieceGrabbed(bool grabbed)
{
	this->Grabbed = grabbed;
}

bool Figura::PieceGrab()
{
	return Grabbed;
}

int Figura::numberOfPiece()
{
	int numberOfFigure;
		if (this->Nazwa == "P")
			numberOfFigure = 0;
		if (this->Nazwa == "K")
			numberOfFigure = 1;
		if (this->Nazwa == "H")
			numberOfFigure = 2;
		if (this->Nazwa == "S")
			numberOfFigure = 3;
		if (this->Nazwa == "G")
			numberOfFigure = 4;
		if (this->Nazwa == "W")
			numberOfFigure = 5;

	return numberOfFigure;
}


>>>>>>> 62aa2c46b80bd51f4099328a85205c0098f2123f
