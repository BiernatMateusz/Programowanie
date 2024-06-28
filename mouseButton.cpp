#include "mouseButton.h"


mouseButton::mouseButton(sf::Mouse::Button MouseButton)
{
	this->MouseButton = MouseButton;
}

void mouseButton::update(sf::RenderWindow* window, sf::Sprite* backGround)
{
	if (sf::Mouse::isButtonPressed(this->MouseButton))
		this->isPressed = 1;
	else this->isPressed = 0;

	this->isNotPressed = not(this->isPressed);

	this->mousePos = sf::Mouse::getPosition(*window);


	setStates();
	setMouseStates(window);
	
	//Setting coordinates of tile clicked - [x][y] 
	if (this->oneSignalPressed)
		setMouseTile(window, backGround);

}

void mouseButton::setMouseTile(sf::RenderWindow* window, sf::Sprite* BackGround)
{
	if (BackGround != nullptr)
	{
		int x = ((int)BackGround->getGlobalBounds().height - (int)BackGround->getPosition().y);
		this->mouseTile = { (this->mousePos.x - (int)BackGround->getPosition().x) / 44,((mousePos.y + (x)) / 44)  };

		//std::cout << "x=" << mouseTile.x << " y=" << mouseTile.y << "\n";
	}
}

const sf::Vector2i& mouseButton::mousePosGet() const
{
	return this->mousePos;
}

const sf::Vector2i& mouseButton::mousePosPrevGet() const
{
	return this->mousePosPrev;
}

const sf::Vector2i& mouseButton::mouseTileGet() const
{
	return this->mouseTile;
}

void mouseButton::setMouseStates(sf::RenderWindow *window)
{
	if (oneSignalButtonPressed())
		this->mousePosPrev = sf::Mouse::getPosition(*window);
}
