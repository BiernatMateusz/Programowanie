#include "Game.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 800), "Gierka");
    this->window->setFramerateLimit(120);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initSzachownica()
{
    this->szachownica = new Szachownica;
    std::cout << "Mamy nowa szachownice: " << szachownica << std::endl;
}

Game::Game()
{
    this->initWindow();
    this->initSzachownica();
}

Game::~Game()
{
	delete this->window;
    delete this->szachownica;
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
}

void Game::render()
{
    this->window->clear();


    //Render items

    szachownica->renderBoard(window);
    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->update();
        this->render();
    }    
}


