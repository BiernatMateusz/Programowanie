#include "StateMenu.h"

StateMenu::StateMenu(GraphicsData* graphicsData, std::stack<State*>* Stat)
	: State(graphicsData, Stat)
{
	initGraphics();
}

StateMenu::~StateMenu()
{

}

void StateMenu::updateKeybinds(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	if (AllKeys.at("LeftMouse")->isButtonPressed())
	{
		if (this->checkExactPosition(316, 735, 288, 435))
			stat->push(new StateSpawnPlace(this->graphicsData, this->stat));

		if (this->checkExactPosition(350, 814, 580, 705))
		{
			//Quit
		}
	}

	this->checkForQuit(AllKeys);
}


void StateMenu::endState()
{
	std::cout << "Ending Menustate\n";
}


void StateMenu::initGraphics()
{
	LoadBackground({ 0,0 }, "Menu");

	this->Camer = new Camera(this->graphicsData);
}

void StateMenu::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	this->updateKeybinds(dt, AllKeys);
	this->getMousePosition();
}

void StateMenu::render()
{
	Camer->render(this->graphicsData->window);
}
