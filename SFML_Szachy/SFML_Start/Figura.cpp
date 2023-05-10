#include "Figura.h"

Figura::Figura(std::string Nazwa, bool kolor)
{
	this->Nazwa = Nazwa;
	this->kolor = kolor;
}

Figura::~Figura()
{

}

std::string Figura::nazwaFigury()
{
	return this->Nazwa;
}
