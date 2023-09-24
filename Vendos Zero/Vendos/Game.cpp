#include "Game.h"

void Game::initializeWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->WindowLenght,this->WindowHight),"Vendos");
	this->window->setFramerateLimit(240);
	this->window->setVerticalSyncEnabled(false);
	this->window->setKeyRepeatEnabled(false);
}

Game::Game()
{
	this->initializeWindow();
	this->initStates();
}

Game::~Game()
{
	delete this->window;
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}

}

void Game::updateSfEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	this->updateSfEvents();
	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			//Save game before then do that 
			this->states.top()->endState();

			delete this->states.top();
			this->states.pop();
		}

	}
	else
	{
		this->endApp();
		this->window->close();
	}

}

void Game::updateDT()
{
	this->dt = this->dtClock.restart().asSeconds();

}

void Game::render()
{
	this->window->clear();
	if (!this->states.empty())
	{
		this->states.top()->render(this->window);
	}

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDT();
		this->update();
		this->render();
	}
}

void Game::initStates()
{
	this->states.push(new StateMenu(this->window, &this->states));
}


void Game::endApp()
{
	std::cout << "KONIEC\n";
}
