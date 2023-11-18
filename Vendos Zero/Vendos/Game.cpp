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
	this->graphicsData = new GraphicsData;
	this->graphicsData->TextureDataMap = &this->TextureDataMap;
	this->initializeWindow();
	this->initTextures();
	this->initStates();
	
}

Game::~Game()
{
	delete this->window;
	delete this->graphicsData;
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

void Game::LoadNewGraphic(std::string&& name)
{
	this->graphicsData->GraphicsTxtVec->push_back(new sf::Texture);
	this->graphicsData->GraphicsTxtVec->back()->loadFromFile("Texture/" + name + ".png");
	this->graphicsData->TexturesMap->insert(std::pair<std::string, sf::Texture*>(name, this->graphicsData->GraphicsTxtVec->back()));

	//new
	this->TextureDataMap.insert(std::pair<std::string, TextureData*>(name, new TextureData));
	this->TextureDataMap[name]->texture = new sf::Texture;
	this->TextureDataMap[name]->texture->loadFromFile("Texture/" + name + ".png");
}

void Game::LoadNewGraphic(std::string&& name, sf::Vector2i blockadeSize,  sf::Vector2i origin, float offsetForPositon, bool blockade)
{
	this->TextureDataMap[name]->blockade = blockade;
	this->TextureDataMap[name]->blockadeSize = blockadeSize;
	this->TextureDataMap[name]->origin = origin;
	this->TextureDataMap[name]->offsetForPositon = offsetForPositon;

	LoadNewGraphic(std::move(name));
	

}

void Game::initStates()
{
	this->states.push(new StateMenu(this->graphicsData, &this->states));
}

void Game::initTextures()
{
	this->TexturesMapPtr = &this->TexturesMap;
	this->GraphicsTxtVecPtr = &this->GraphicsTxtVec;
	initGraphicsData();
	//Main menu
	LoadNewGraphic("Menu");


	//Terrain
	LoadNewGraphic("Mapka");
	LoadNewGraphic("Tree1");
	LoadNewGraphic("Tree2");
	LoadNewGraphic("Tree3");
	LoadNewGraphic("Tree1", { 30,30 }, {50,-40},-15,1); 
	LoadNewGraphic("Tree2", { 30,30 }, { 68,0 }, -15, 1); 
	LoadNewGraphic("Tree3", { 30,20 }, { 47,-30 }, -15, 1); 

	//Player
	LoadNewGraphic("Abigail");

	//Equipment
	LoadNewGraphic("Dziabka");
	LoadNewGraphic("Kilof");
	LoadNewGraphic("Siekiera");
	LoadNewGraphic("Miecz");
	LoadNewGraphic("Lopata");
	LoadNewGraphic("Konewka");

	//Field
	LoadNewGraphic("PoDziabceSuche");
	LoadNewGraphic("PoDziabceMokre");
}

void Game::initGraphicsData()
{
	this->graphicsData->window = this->window;
	this->graphicsData->TexturesMap = this->TexturesMapPtr;
	this->graphicsData->GraphicsTxtVec = this->GraphicsTxtVecPtr;
}


void Game::endApp()
{

	for (auto* elem : GraphicsTxtVec)
		delete elem;
	GraphicsTxtVec.clear();
	TexturesMap.clear();

	std::cout << "KONIEC\n";
}
