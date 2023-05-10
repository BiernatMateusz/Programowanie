#ifndef FIGURA_H
#define FIGURA_H

#include <string>

class Figura
{
private:
	std::string Nazwa;		//W //S //G //H //K //P
	bool kolor;				//0 biale //1 czarne
public:
	Figura(std::string Nazwa, bool kolor);
	virtual ~Figura();

	//Functions
	std::string nazwaFigury();


};

#endif