#include "StateMenu.h"

StateMenu::StateMenu(sf::RenderWindow* window, std::stack<State*>* Stat)
	: State(window, Stat)
{
	initGraphics();
}

StateMenu::~StateMenu()
{
	for (auto& elem : GraphicsSprite)
		delete elem;
	for (auto& elem : GraphicsTxtVec)
		delete elem;


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
	this->GraphicsTxtVec.push_back(new sf::Texture);
	this->GraphicsTxtVec.back()->loadFromFile("Texture/Menu.png");
	GraphicsSprite.push_back(new sf::Sprite);
	this->GraphicsSprite.back()->setTexture(*this->GraphicsTxtVec.back());


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
