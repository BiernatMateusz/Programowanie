#include "Equipment.h"

Equipment::Equipment(GraphicsData* graphicsData)
{
	this->graphicsData = graphicsData;
	this->equipmentData = new EquipmentData;
	this->BottomBarTxtPtr = new sf::Texture;
	this->BottomBarPtr = new sf::Sprite;
	this->BottomBarChoosenTxtPtr = new sf::Texture;
	this->BottomBarChoosenPtr = new sf::Sprite;

	initEqAndBar();

	calculatePositionOfFirstItem();

	initGraphics();
	initBottomBar();
}

void Equipment::initBottomBar()
{
	//this->BottomBarSprites.push_back(this->graphicsData->SpritesMap["Miecz"]);
	//this->BottomBarSprites.push_back(this->graphicsData->SpritesMap["Kilof"]);
	//this->BottomBarSprites.push_back(this->graphicsData->SpritesMap["Siekiera"]);
	//this->BottomBarSprites.push_back(this->graphicsData->SpritesMap["dziabka"]);
	//this->BottomBarSprites.push_back(this->graphicsData->SpritesMap["konewka"]);
	//this->BottomBarSprites.push_back(this->graphicsData->SpritesMap["lopata"]);

	//while (BottomBarSprites.size() < this->NumberOfItems)
	//{
	//	BottomBarSprites.push_back(nullptr);
	//}
}

void Equipment::updateBottomBar()
{
	for (int i = 0; i < this->sizeOfEq.x; ++i)
	{
		if (BotBarPtr[i] == nullptr && Eq[i][0] != nullptr)
		{
			BotBarPtr[i] = new item;
		}

		if (BotBarPtr[i] != nullptr && Eq[i][0] == nullptr)
		{
			BotBarPtr[i] = nullptr;
		}
		
		if (BotBarPtr[i]!= nullptr && Eq[i][0]!= nullptr)
		{
			*this->BotBarPtr[i] = *this->Eq[i][0];
			this->BotBarPtr[i]->itemSprite.setPosition(this->equipmentData->FirstItemPosition.x + (i * this->equipmentData->SizeOfItems), this->equipmentData->FirstItemPosition.y);
		}

	}
	
}



void Equipment::calculatePositionOfFirstItem()
{
	this->MapBorder = { (float)this->graphicsData->window->getSize().x,(float)this->graphicsData->window->getSize().y };
	this->equipmentData->FirstItemPosition = { (this->MapBorder.x / 2)-(this->NumberOfItems/2*this->equipmentData->SizeOfItems),this->MapBorder.y - this->equipmentData->Y_Offset_Bar_From_Border };
}

void Equipment::updateKeybinds()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		this->equipmentData->whichItemSelected = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		this->equipmentData->whichItemSelected = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		this->equipmentData->whichItemSelected = 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		this->equipmentData->whichItemSelected = 3;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		this->equipmentData->whichItemSelected = 4;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
		this->equipmentData->whichItemSelected = 5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
	{
		this->equipmentData->whichItemSelected = 6;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
	{
		this->equipmentData->whichItemSelected = 7;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
	{
		this->equipmentData->whichItemSelected = 8;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
	{
		this->equipmentData->whichItemSelected = 9;
	}

	changeBar();
}

void Equipment::changeBar()
{
	BottomBarChoosenPtr->setPosition(this->equipmentData->FirstItemPosition.x + (this->equipmentData->SizeOfItems * this->equipmentData->whichItemSelected), this->equipmentData->FirstItemPosition.y);
}

void Equipment::initGraphics()
{
	BottomBarTxtPtr->loadFromFile("Texture/Ramka.png");
	BottomBarPtr->setTexture(*this->BottomBarTxtPtr);
	BottomBarPtr->setPosition(this->equipmentData->FirstItemPosition.x, this->equipmentData->FirstItemPosition.y);

	BottomBarChoosenTxtPtr->loadFromFile("Texture/Ramka1.png");
	BottomBarChoosenPtr->setTexture(*this->BottomBarChoosenTxtPtr);
	BottomBarChoosenPtr->setPosition(this->equipmentData->FirstItemPosition.x, this->equipmentData->FirstItemPosition.y);

}

void Equipment::update()
{
	updateKeybinds();
	updateBottomBar();
}

void Equipment::render()
{
	
	drawBottomBar();
	drawEq();
	

}

void Equipment::initEqAndBar()
{
	//std::vector<std::vector<int>> twoDVector(rows, std::vector<int>(columns, initialValue));
	this->Eq.resize(this->sizeOfEq.x, std::vector<item*>(this->sizeOfEq.y,nullptr));
	this->BotBarPtr.resize(this->sizeOfEq.x,nullptr);

	sf::Vector2i xyOfVec{ 0,0 };

	this->Eq[xyOfVec.x][xyOfVec.y] = new itemHoe(this->graphicsData, this->equipmentData, xyOfVec, "dziabka");

	xyOfVec={ 1,0 };

	this->Eq[xyOfVec.x][xyOfVec.y] = new itemPickaxe(this->graphicsData, this->equipmentData, xyOfVec, "Kilof");

	xyOfVec = { 2,0 };

	this->Eq[xyOfVec.x][xyOfVec.y] = new itemPickaxe(this->graphicsData, this->equipmentData, xyOfVec, "konewka");

	xyOfVec = { 3,0 };

	this->Eq[xyOfVec.x][xyOfVec.y] = new itemAxe(this->graphicsData, this->equipmentData, xyOfVec, "siekiera");

	xyOfVec = { 4,0 };

	this->Eq[xyOfVec.x][xyOfVec.y] = new itemSword(this->graphicsData, this->equipmentData, xyOfVec, "Miecz");

	xyOfVec = { 5,0 };

	this->Eq[xyOfVec.x][xyOfVec.y] = new itemSword(this->graphicsData, this->equipmentData, xyOfVec, "lopata");



	updateBottomBar();

}

void Equipment::drawEq()
{
	
}

void Equipment::drawBottomBar()
{
	for (int i = 0; i < this->NumberOfItems; i++)
	{
		BottomBarPtr->setPosition(this->equipmentData->FirstItemPosition.x + (i * this->equipmentData->SizeOfItems), this->equipmentData->FirstItemPosition.y);
		this->graphicsData->window->draw(*this->BottomBarPtr);
	}
	this->graphicsData->window->draw(*this->BottomBarChoosenPtr);

	for (int i = 0; i < this->BotBarPtr.size(); i++)
	{
		if (BotBarPtr[i] != nullptr)
		{
			BotBarPtr[i]->render();
		}
	}
}

