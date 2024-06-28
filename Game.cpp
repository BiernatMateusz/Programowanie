#include "Game.h"

//Constructors
Game::Game()
{
	this->initAllKeys();
	this->initializeWindow();
	this->initGraphicsData();
	this->initTextures();
	this->initStates();
}

//Destructor
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

//Update and render functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDT();
		this->update();
		this->render();
	}
}

void Game::updateSfEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();

		/*if (this->sfEvent.type == sf::Event::MouseWheelMoved)
		{
			if (this->sfEvent.mouseWheel.delta > 0)
			{
				std::cout << "Krece w gore :)\n";
			}
			else if (this->sfEvent.mouseWheel.delta < 0)
			{
				std::cout << "Krece w dol :)\n";
			}
		}*/
	}
}

void Game::update()
{
	this->updateSfEvents();

	//Keys update
	if (this->graphicsData->window!=nullptr)
		std::for_each(AllKeys.begin(), AllKeys.end(), [this](auto& keys) {keys.second->update(this->graphicsData->window, this->graphicsData->backGround); });

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt, this->AllKeys);

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
		this->states.top()->render();
	}

	this->window->display();
}

void Game::endApp()
{
	std::cout << "KONIEC\n";
}

//Init functions
void Game::initializeWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(this->WindowLenght, this->WindowHight), "Vendos");
	this->window->setFramerateLimit(240);
	this->window->setVerticalSyncEnabled(false);
	this->window->setKeyRepeatEnabled(false);
}

void Game::initAllKeys()
{
	this->AllKeys.insert({ "A", new button(sf::Keyboard::A)});
	this->AllKeys.insert({ "S", new button(sf::Keyboard::S)});
	this->AllKeys.insert({ "D", new button(sf::Keyboard::D)});
	this->AllKeys.insert({ "W", new button(sf::Keyboard::W)});
	this->AllKeys.insert({ "E", new button(sf::Keyboard::E)});
	this->AllKeys.insert({ "Esc", new button(sf::Keyboard::Escape)});
	this->AllKeys.insert({ "LShift", new button(sf::Keyboard::LShift) });
	this->AllKeys.insert({ "LeftMouse", new mouseButton(sf::Mouse::Left)});
	this->AllKeys.insert({ "RightMouse", new mouseButton(sf::Mouse::Right)});
	this->AllKeys.insert({ "Num0", new button(sf::Keyboard::Num0) });
	this->AllKeys.insert({ "Num1", new button(sf::Keyboard::Num1) });
	this->AllKeys.insert({ "Num2", new button(sf::Keyboard::Num2) });
	this->AllKeys.insert({ "Num3", new button(sf::Keyboard::Num3) });
	this->AllKeys.insert({ "Num4", new button(sf::Keyboard::Num4) });
	this->AllKeys.insert({ "Num5", new button(sf::Keyboard::Num5) });
	this->AllKeys.insert({ "Num6", new button(sf::Keyboard::Num6) });
	this->AllKeys.insert({ "Num7", new button(sf::Keyboard::Num7) });
	this->AllKeys.insert({ "Num8", new button(sf::Keyboard::Num8) });
	this->AllKeys.insert({ "Num9", new button(sf::Keyboard::Num9) });

}

void Game::initStates()
{
	this->states.push(new StateMenu(this->graphicsData, &this->states));
}

void Game::initTextures()
{
	//Main menu
	LoadNewGraphic("Menu",0);


	//Terrain
	LoadNewGraphic("Mapka", 1);

	//Player
	LoadNewGraphic("Abigail", 2);

	//Field
	LoadNewGraphic("PoDziabceSuche", { 0,0 }, { 0,-44 }, -44, 0, 5, 3);
	LoadNewGraphic("PoDziabceMokre", { 0,0 }, { 0,-44 }, -44, 0, 6, 4);

	//Pickaxable map
	LoadNewGraphic("Stone", { 30,30 }, { 0,-44 }, -50, 1, 3, 5);

	//Trees
	LoadNewGraphic("Tree1", { 30,30 }, { 50,-40 }, -15, 1, 2,10);
	LoadNewGraphic("Tree2", { 30,30 }, { 68,0 }, -15, 1, 2, 11);
	LoadNewGraphic("Tree3", { 30,20 }, { 47,-30 }, -15, 1, 2, 12);


	//Equipment
	// 
	//Nonstackable
	LoadNewGraphic("Dziabka",20);
	LoadNewGraphic("Kilof",21);
	LoadNewGraphic("Siekiera",22);
	LoadNewGraphic("Miecz",23);
	LoadNewGraphic("Lopata",24);
	LoadNewGraphic("Konewka",25);

	//Chest
	LoadNewGraphic("Skrzynia", { 32,20 }, { 0,0 }, 0, 1, 8, 26);
	//Stackable

	LoadNewGraphic("StoneEq",100);
	LoadNewGraphic("WoodEq", 101);


	
	
}

void Game::initGraphicsData()
{
	this->graphicsData = new GraphicsData;

	this->graphicsData->TextureDataMap = new std::map<std::string, TextureData*>;
	this->graphicsData->window = this->window;
	this->graphicsData->TexturesMap = new std::map<std::string, sf::Texture*>;
	this->graphicsData->GraphicsTxtVec = new std::vector<sf::Texture*>;
}

//Graphics functions 
void Game::LoadNewGraphic(std::string&& name, int itemID)
{
	this->graphicsData->GraphicsTxtVec->push_back(new sf::Texture);
	this->graphicsData->GraphicsTxtVec->back()->loadFromFile("Texture/" + name + ".png");
	this->graphicsData->TexturesMap->insert(std::pair<std::string, sf::Texture*>(name, this->graphicsData->GraphicsTxtVec->back()));

	this->graphicsData->TextureDataMap->insert(std::pair<std::string, TextureData*>(name, new TextureData));
	this->graphicsData->TextureDataMap->at(name)->texture = new sf::Texture;
	this->graphicsData->TextureDataMap->at(name)->texture->loadFromFile("Texture/" + name + ".png");

	this->graphicsData->TextureDataMap->at(name)->initBlocksOccupied(name, graphicsData);
	this->graphicsData->TextureDataMap->at(name)->itemID = itemID;
	
}

void Game::LoadNewGraphic(std::string&& name, sf::Vector2i blockadeSize,  sf::Vector2i origin, float offsetForPositonY, bool blockade, int typeOfTile, int itemID)
{
	LoadNewGraphic(std::move(name), itemID);

	this->graphicsData->TextureDataMap->at(name)->blockade = blockade;
	this->graphicsData->TextureDataMap->at(name)->blockadeSize = blockadeSize;
	this->graphicsData->TextureDataMap->at(name)->origin = origin;
	this->graphicsData->TextureDataMap->at(name)->offsetForPositonY = offsetForPositonY;
	this->graphicsData->TextureDataMap->at(name)->typeOfTile = typeOfTile;
}

