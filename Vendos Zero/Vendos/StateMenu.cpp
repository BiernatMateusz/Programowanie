#include "StateMenu.h"

StateMenu::StateMenu(GraphicsData* graphicsData, std::stack<State*>* Stat)
	: State(graphicsData, Stat)
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
			
			stat->push(new StateSpawnPlace(this->graphicsData, this->stat));
			

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


void StateMenu::initEquipment(GraphicsData* graphicsData)
{

}

void StateMenu::initGraphics()
{
	LoadNewGraph({ 0,0 }, "Menu");

	this->Camer = new Camera(&this->GraphicsSprite, this->graphicsData->window);
}

void StateMenu::update(const float& dt)
{
	this->updateKeybinds(dt);
	this->getMousePosition();

}

void StateMenu::render(sf::RenderTarget* Window)
{
	Camer->render(this->graphicsData->window);
}
