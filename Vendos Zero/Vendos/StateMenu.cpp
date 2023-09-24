#include "StateMenu.h"

StateMenu::StateMenu(sf::RenderWindow* window, std::stack<State*>* Stat)
	: State(window, Stat)
{
	initGraphics();
}

StateMenu::~StateMenu()
{

}

void StateMenu::updateKeybinds(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->checkExactPosition(316, 735, 288, 435))
		{
			std::cout << "1\n";
			stat->push(new StateSpawnPlace(window, this->stat));

		}
		if (this->checkExactPosition(350, 814, 580, 705))
		{
			std::cout << "2\n";

		}
	}

	this->checkForQuit();
}


void StateMenu::endState()
{
	std::cout << "Ending Menustate\n";
}

void StateMenu::initGraphics()
{
	this->GraphicsTxt.loadFromFile("Texture/Menu.png");
	this->GraphicsSprite.setTexture(this->GraphicsTxt);
}

void StateMenu::update(const float& dt)
{
	this->updateKeybinds(dt);
	this->getMousePosition();

}

void StateMenu::render(sf::RenderTarget* Window)
{
	Window->draw(this->GraphicsSprite);
}
