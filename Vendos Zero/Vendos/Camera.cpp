#include "Camera.h"

bool operator>(const sf::Sprite &x,const sf::Sprite &y)
{
	std::cout << &x << " a teraz wysokosc\n";
	return (y.getPosition().y+y.getGlobalBounds().height ) > (x.getPosition().y+x.getGlobalBounds().height);
}


Camera::Camera(std::vector<sf::Sprite*>* GraphicsSpr, sf::RenderWindow* window)
{
	this->Window = window;
	this->AllSpritesPointer = &this->AllSprites;
	*this->AllSpritesPointer = *GraphicsSpr;
	sortVector(this->AllSpritesPointer);

}

Camera::Camera(std::vector<sf::Sprite*>* GraphicsSpr, std::vector<sf::Sprite*>* EntitySpr, sf::RenderWindow* window)
{
	this->Window = window;
	this->AllSpritesPointer = &this->AllSprites;
	*this->AllSpritesPointer = *GraphicsSpr;

	
	AllSpritesPointer->insert(AllSpritesPointer->end(), EntitySpr->begin(), EntitySpr->end());
	std::cout << "Wskaznik AllSprite1: " << this->AllSpritesPointer->at(0) << "\n";
	sortVector(this->AllSpritesPointer);
	
}

Camera::~Camera()
{

}


void Camera::sortVector(std::vector<sf::Sprite*>* &AllSpr)
{
	std::cout << "Wskaznik AllSprite1: " << this->AllSpritesPointer->at(0) << "\n";

	std::sort(AllSpr->begin(), AllSpr->end(), 
		[this]( sf::Sprite *&y,  sf::Sprite *&x) -> bool 
			{
			std::cout << y << "\n";
			return *y>*x; 
			}
		);
}


void Camera::render(sf::RenderWindow* window)
{
	//Function enables us to draw background at the beggining then all sprites
	window->draw(*this->AllSpritesPointer->back());
	for (int i=0;i<this->AllSpritesPointer->size()-1;++i)
	window->draw(*this->AllSpritesPointer->at(i));

}
