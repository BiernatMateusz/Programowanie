#include "State.h"

State::State(sf::RenderWindow* Window, std::stack<State*> *Stat, std::map<std::string, sf::Texture*>* TexturesMap, std::vector<sf::Texture*>* GraphicsTxtVecToP)
{
	this->window = Window;
	this->stat = Stat;
	this->quit = false;
	this->SpritesEntiPointer = &this->SpritesEnti;
	this->entiesPointer = &this->entities;
	this->TexturesMap = TexturesMap;
	this->GraphicsTxtPointer = GraphicsTxtVecToP;
	
}

State::~State()
{
	delete window;
	delete NewEntity;
	std::cout << "Usunalem stat\n";
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::getMousePosition()
{
	this->mousePosition.x = sf::Mouse::getPosition().x - this->window->getPosition().x;
	this->mousePosition.y = sf::Mouse::getPosition().y - this->window->getPosition().y;
}

bool State::checkExactPosition(int x,int offsetX,int y,int offsetY)
{
		return (mousePosition.x > x && mousePosition.x < offsetX && mousePosition.y>y && mousePosition.y < offsetY);
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
	this->GraphicsSprite.push_back(new sf::Sprite);
	this->GraphicsSprite.back()->setTexture(*this->TexturesMap->at(NameOfTxt));

	//Setting origins
	if (NameOfTxt == "Mapka")
		this->GraphicsSprite.back()->setOrigin(0, this->GraphicsSprite.back()->getGlobalBounds().height);

	if (NameOfTxt == "Tree1")
	{
		this->GraphicsSprite.back()->setOrigin(50, this->GraphicsSprite.back()->getGlobalBounds().height - 25-44);
		this->BlockadeDimension[position.x / 44][position.y / 44] = {30,30};
	}


	this->GraphicsSprite.back()->setPosition(position.x, position.y);

	if (Blockade.size() > 0)
	{
		std::cout << "BLOKADA: " << position.x / 44 << " i " << position.y / 44 << "\n";
		this->Blockade[position.x / 44][position.y / 44] = 1;
	}
	

}
