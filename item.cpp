#include "item.h"

void item::updateAndRenderNumberOfItems()
{
	this->numberOfItems.setString(std::to_string(numberOfItemsInStack));
	this->numberOfItems.setCharacterSize(16);
	this->numberOfItems.setPosition(
		this->itemSprite.getPosition().x + 80 - numberOfItems.getGlobalBounds().width,
		this->itemSprite.getPosition().y + 62);
	this->Window->draw(this->numberOfItems);
}

void item::updateKeybinds(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		this->equipmentData->actionIsHappening = checkClickedTile((sf::Vector2i)AllKeys.at("LeftMouse")->mouseTileGet());
}

void item::initPositon(sf::Vector2i xyOfvec, sf::Vector2f FirstItemPos, const int& itemSize, int OffsetYPositioning)
{
	this->itemSprite.setPosition(FirstItemPos.x + xyOfvec.x*itemSize, FirstItemPos.y- (-xyOfvec.y+2) * itemSize - OffsetYPositioning*itemSize);
}

void item::initGraphics(std::string &&name)
{
	this->itemSprite.setTexture(*this->graphicsData->TexturesMap->at(name));
	this->itemID = this->graphicsData->TextureDataMap->at(name)->itemID;
}

bool item::checkTile(sf::Vector2i&& position2i, std::vector<int>* TypeOfBlockToInterract, bool nullptrable)
{
	bool possible{};

	if ((*this->Tile)[position2i.x][position2i.y] != nullptr)
	{
		for (int i=0;i<TypeOfBlockToInterract->size();++i)
		{
			if ((*this->Tile)[position2i.x][position2i.y]->typeOfTile == (*TypeOfBlockToInterract)[i])
				possible = 1;
		}
	}
	else if (nullptrable==1) possible = 1;

	

	return possible; //*TODO
}

void item::initTile(sf::Vector2i&& position2i, std::string&& NameOfTxt)
{
	//While setting position we need to know exact position of background 

	(*this->Tile)[position2i.x][position2i.y]= new TilesOnMap(position2i, NameOfTxt, graphicsData);

	this->nameOfTxt = NameOfTxt;
}

item::item(GraphicsData* graphicsData)
{
	this->graphicsData = graphicsData;
	this->Window = graphicsData->window;

	this->font.loadFromFile("Font/Rinnero.ttf");
	this->numberOfItems.setFont(font);
	this->numberOfItems.setFillColor(sf::Color::Black);
	this->numberOfItems.setStyle(sf::Text::Bold);
}

item::item(GraphicsData* graphicsData, EquipmentData* equipmentData, std::string&& name, std::vector<std::vector<TilesOnMap*>>*Tile)
	:
	item(graphicsData)
{
	this->equipmentData = equipmentData;
	this->Tile = Tile;

	initGraphics(std::move(name));
	//initPositon(xyOfvec, equipmentData->FirstItemPosition, equipmentData->SizeOfItems);
}

item& item::operator=(const item& model)
{
	if (&model != this)
	{
		font = model.font;
		numberOfItems = model.numberOfItems;
		maxStack = model.maxStack;
		OverMax = model.OverMax;
		Window = model.Window;
		graphicsData = model.graphicsData;
		equipmentData = model.equipmentData;
		Tile = model.Tile;
		numberOfItemsInStack = 1; //model.numberOfItemsInStack 
		nameOfTxt = model.nameOfTxt;
		timeOfItemUsage = model.timeOfItemUsage;
		timePassed = 0;
		nameOfTxt = model.nameOfTxt;
		itemID = model.itemID;
		itemSprite = model.itemSprite;
	}
	return *this;
}

void item::changeNumberOfItems(int newNumberOfItems)
{
	this->numberOfItemsInStack = newNumberOfItems;
}

int item::getNumberOfItems()
{
	return this->numberOfItemsInStack;
}

int item::getNumberMax()
{
	return this->maxStack;
}

bool item::addItemsReturn1IfOverMax(item* itemPtr)
{
	this->OverMax = 0;
	
	if ((this->numberOfItemsInStack + itemPtr->numberOfItemsInStack) > maxStack)
	{
		OverMax = true;
		itemPtr->numberOfItemsInStack = itemPtr->numberOfItemsInStack + this->numberOfItemsInStack - maxStack;
		this->numberOfItemsInStack = maxStack;
	}
	else
		this->numberOfItemsInStack += itemPtr->numberOfItemsInStack;

	return OverMax;
}

void item::substrFromThisItem(int value)
{
	this->numberOfItemsInStack -= value;
}

void item::addToThisItem(int value)
{
	this->numberOfItemsInStack += value;
}

bool item::checkIfAddable()
{
	if (this->itemID >= 100)
		if (this->numberOfItemsInStack < this->maxStack)
			return true;
	return false;
}

void item::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	updateKeybinds(dt, AllKeys);
}

void item::render()
{
	this->Window->draw(this->itemSprite);
	updateAndRenderNumberOfItems();

}

bool item::checkClickedTile(sf::Vector2i&& position2i)
{
	bool possibleClick{};

	if (position2i.x <= this->Tile->size() 
		and position2i.x >= 0
		and position2i.y <= (*Tile)[0].size()
		and position2i.y >= 0)
		possibleClick = 1;

	return possibleClick;
}



