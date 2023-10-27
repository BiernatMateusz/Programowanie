#include "StateMenu.h"

StateMenu::StateMenu(sf::RenderWindow* window, std::stack<State*>* Stat, std::map<std::string, sf::Texture*>* TexturesMap, std::vector<sf::Texture*>* GraphicsTxtVecToP)
	: State(window, Stat, TexturesMap, GraphicsTxtVecToP)
{
	initGraphics();
}

StateMenu::~StateMenu()
{
	for (auto* elem : GraphicsSprite)
		delete elem;
}

void StateMenu::updateKeybinds(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->checkExactPosition(316, 735, 288, 435))
		{
			std::cout << "1\n";
			
			stat->push(new StateSpawnPlace(window, this->stat, this->TexturesMap, this->GraphicsTxtPointer ));
			
			

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
	LoadNewGraph({ 0,0 }, "Menu");

	this->Camer = new Camera(&this->GraphicsSprite, window);
}

void StateMenu::update(const float& dt)
{
	this->updateKeybinds(dt);
	this->getMousePosition();

}

void StateMenu::render(sf::RenderTarget* Window)
{
	Camer->render(window);
}
