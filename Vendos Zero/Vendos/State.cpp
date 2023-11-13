#include "State.h"

State::State(GraphicsData* graphicsData, std::stack<State*>* Stat)
{
	this->graphicsData = graphicsData;
	this->stat = Stat;
	this->quit = false;
	this->SpritesEntiPointer = &this->SpritesEnti;

	this->graphicsData->GraphicsSprite = &this->GraphicsSprite;
	for (auto* elem : *this->graphicsData->GraphicsSprite)
		delete elem;

	this->graphicsData->GraphicsSprite->clear();

	this->entiesPointer = &this->entities;

}

State::~State()
{
	delete this->graphicsData->window;
	delete NewEntity;
	std::cout << "Usunalem stat\n";
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::getMousePosition()
{
	this->graphicsData->mousePosition.x = sf::Mouse::getPosition().x - this->graphicsData->window->getPosition().x;
	this->graphicsData->mousePosition.y = sf::Mouse::getPosition().y - this->graphicsData->window->getPosition().y;
}

bool State::checkExactPosition(int x,int offsetX,int y,int offsetY)
{
		return (this->graphicsData->mousePosition.x > x && this->graphicsData->mousePosition.x < offsetX && this->graphicsData->mousePosition.y>y && this->graphicsData->mousePosition.y < offsetY);
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit = true;
	}
}

void State::LoadNewGraph(sf::Vector2f&& position, std::string&& NameOfTxt)
{
	float offset{};
	this->graphicsData->GraphicsSprite->push_back(new sf::Sprite);
	this->graphicsData->GraphicsSprite->back()->setTexture(*this->graphicsData->TexturesMap->at(NameOfTxt));

	//Setting origins
	if (NameOfTxt == "Mapka")
		this->graphicsData->GraphicsSprite->back()->setOrigin(0, this->graphicsData->GraphicsSprite->back()->getGlobalBounds().height);

	if (NameOfTxt == "Tree1")
	{
		this->graphicsData->GraphicsSprite->back()->setOrigin(50, this->graphicsData->GraphicsSprite->back()->getGlobalBounds().height - 25 -15 ); //-44
		this->BlockadeDimension[position.x / 44][(position.y / 44)-1] = {30,30};
		offset = -15;
	}

	if (NameOfTxt == "Tree2")
	{
		this->graphicsData->GraphicsSprite->back()->setOrigin(68, this->graphicsData->GraphicsSprite->back()->getGlobalBounds().height);
		this->BlockadeDimension[position.x / 44][(position.y / 44) - 1] = { 30,30 };    
		offset = -15;
	}

	if (NameOfTxt == "Tree3")
	{
		this->graphicsData->GraphicsSprite->back()->setOrigin(47, this->graphicsData->GraphicsSprite->back()->getGlobalBounds().height-30); //-44
		this->BlockadeDimension[position.x / 44][(position.y / 44) - 1] = { 30,10 };     
		offset = -15;
	}


	this->graphicsData->GraphicsSprite->back()->setPosition(position.x, position.y+offset);

	if (Blockade.size() > 0)
	{
		this->Blockade[position.x / 44][(position.y / 44)-1] = 1;
	}
	

}
