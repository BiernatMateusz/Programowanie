#include "Equipment.h"

void Equipment::initBottomBar()
{
	this->BottomBarSprites.push_back(this->graphicsData->SpritesMap["Miecz"]);
	this->BottomBarSprites.push_back(this->graphicsData->SpritesMap["Kilof"]);
	this->BottomBarSprites.push_back(this->graphicsData->SpritesMap["Siekiera"]);
	this->BottomBarSprites.push_back(this->graphicsData->SpritesMap["dziabka"]);
	this->BottomBarSprites.push_back(this->graphicsData->SpritesMap["konewka"]);
	this->BottomBarSprites.push_back(this->graphicsData->SpritesMap["lopata"]);

	while (BottomBarSprites.size() < this->NumberOfItems)
	{
		BottomBarSprites.push_back(nullptr);
	}


}

Equipment::Equipment(GraphicsData* graphicsData)
{
	this->graphicsData = graphicsData;

	initEqAndBar();

	calculatePositionOfFirstItem();

	initGraphics();
	initBottomBar();
}

void Equipment::calculatePositionOfFirstItem()
{
	this->MapBorder = { (float)this->graphicsData->window->getSize().x,(float)this->graphicsData->window->getSize().y };
	this->graphicsData->FirstItemPosition = { (this->MapBorder.x / 2)-(this->NumberOfItems/2*this->graphicsData->SizeOfItems),this->MapBorder.y - this->graphicsData->Y_Offset_Bar_From_Border };
}

void Equipment::updateKeybinds()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		this->WhichItemSelected = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		this->WhichItemSelected = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		this->WhichItemSelected = 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		this->WhichItemSelected = 3;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		this->WhichItemSelected = 4;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
		this->WhichItemSelected = 5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
	{
		this->WhichItemSelected = 6;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
	{
		this->WhichItemSelected = 7;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
	{
		this->WhichItemSelected = 8;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
	{
		this->WhichItemSelected = 9;
	}

	changeBar();
}

void Equipment::changeBar()
{
	BottomBarChoosenPtr->setPosition(this->graphicsData->FirstItemPosition.x + (this->graphicsData->SizeOfItems * WhichItemSelected), this->graphicsData->FirstItemPosition.y);
}

void Equipment::initGraphics()
{
	BottomBarTxtPtr->loadFromFile("Texture/Ramka.png");
	BottomBarPtr->setTexture(*this->BottomBarTxtPtr);
	BottomBarPtr->setPosition(this->graphicsData->FirstItemPosition.x, this->graphicsData->FirstItemPosition.y);

	BottomBarChoosenTxtPtr->loadFromFile("Texture/Ramka1.png");
	BottomBarChoosenPtr->setTexture(*this->BottomBarChoosenTxtPtr);
	BottomBarChoosenPtr->setPosition(this->graphicsData->FirstItemPosition.x, this->graphicsData->FirstItemPosition.y);

	LoadNewGraphic("dziabka");
	LoadNewGraphic("Kilof");
	LoadNewGraphic("Siekiera");
	LoadNewGraphic("Miecz");
	LoadNewGraphic("lopata");
	LoadNewGraphic("konewka");

}

void Equipment::update()
{
	updateKeybinds();
}

void Equipment::render()
{
	drawEq();

	for (int i = 0; i < this->NumberOfItems; i++)
	{
		BottomBarPtr->setPosition(this->graphicsData->FirstItemPosition.x +(i*this->graphicsData->SizeOfItems), this->graphicsData->FirstItemPosition.y);
		this->graphicsData->window->draw(*this->BottomBarPtr);
	}
	this->graphicsData->window->draw(*this->BottomBarChoosenPtr);
	
	for (int i = 0; i < this->NumberOfItems; i++)
	{	if (BottomBarSprites[i]!=nullptr)
		{
			BottomBarSprites[i]->setPosition(this->graphicsData->FirstItemPosition.x + (i * this->graphicsData->SizeOfItems), this->graphicsData->FirstItemPosition.y);
			this->graphicsData->window->draw(*this->BottomBarSprites[i]);
		}
	}

}

void Equipment::initEqAndBar()
{
	//std::vector<std::vector<int>> twoDVector(rows, std::vector<int>(columns, initialValue));
	this->Eq.resize(this->sizeOfEq.x, std::vector<item*>(this->sizeOfEq.y,nullptr));
	sf::Vector2i xyOfVec{ 0,0 };

	this->Eq[xyOfVec.x][xyOfVec.y] = new itemHoe(this->graphicsData, xyOfVec, "dziabka");

	for (int i = 0; i < this->sizeOfEq.x; ++i)
	{
		BotBarPtr.push_back(*Eq[0].data() +i);
	}
}

void Equipment::drawEq()
{
	
}

void Equipment::drawBottomBar()
{

}

void Equipment::LoadNewGraphic(std::string&& name)
{
	this->graphicsData->GraphicsTxtVec->push_back(new sf::Texture);
	this->graphicsData->GraphicsTxtVec->back()->loadFromFile("Texture/" + name + ".png");
	this->graphicsData->TexturesMap->insert(std::pair<std::string, sf::Texture*>(name, this->graphicsData->GraphicsTxtVec->back()));
	this->graphicsData->SpritesMap.insert(std::pair<std::string, sf::Sprite*>(name, new sf::Sprite));
	this->graphicsData->SpritesMap[name]->setTexture(*this->graphicsData->GraphicsTxtVec->back());
}
