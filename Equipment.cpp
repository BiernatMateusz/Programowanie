#include "Equipment.h"


//Constructor
Equipment::Equipment(GraphicsData* graphicsData, std::vector<std::vector<TilesOnMap*>>*Tile, EquipmentData* equipmentData, std::vector<ThrownItems*>* ItemsThrown, ThrownItems* ItemsOnTheGround)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->BottomBarTxtPtr = new sf::Texture;
	this->BottomBarPtr = new sf::Sprite;
	this->BottomBarChoosenTxtPtr = new sf::Texture;
	this->BottomBarChoosenPtr = new sf::Sprite;
	this->Tile = Tile;
	this->ItemsThrown = ItemsThrown;
	this->equipmentManagement = new EquipmentManagement(this->graphicsData, this->equipmentData, &this->Eq,this->ItemsThrown, ItemsOnTheGround);
	this->itemsOnTheGround = ItemsOnTheGround;
	this->itemsOnTheGround->initEqPtr(&this->Eq);


	initEqAndBar();

	calculatePositionOfFirstItemEqAndChest();
	
	this->equipmentData->needToUpdateEq = true;

	initGraphics();
	
}

//Core update functions
void Equipment::updateKeybinds(const std::map<std::string, button*>& AllKeys)
{
	//E key
	openingEquipment(AllKeys);

	//Dealing with chests
	//Doesnt matter what kind of item is in hand function should open the chest
	openingChest(AllKeys);

	//1-9(0) keys
	changingSelectedItem(AllKeys);

	
}

void Equipment::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	//All mechanics based on clicking tiles 
	if (this->equipmentData->isEqOpened == 0 and (this->Eq)[this->equipmentData->whichItemSelected][2]!=nullptr)
		(this->Eq)[this->equipmentData->whichItemSelected][2]->update(dt, AllKeys);

	//All mechanics based on equipment 
	if (this->equipmentData->isEqOpened == 1)
	{
		//movingItems(AllKeys);
		this->equipmentManagement->update(AllKeys);
	}

	this->updatePositionOfItems(); //Updating  position of items in eq and chest after moves

	//this->updateItemsThrown(dt);
	this->itemsOnTheGround->update2(dt);
	
	updateKeybinds(AllKeys); 
}

void Equipment::render()
{
	drawBottomBarLayout();

	if (this->equipmentData->isEqOpened == 0) drawItemsOnBar(); //Draw items on bottom bar

	if (this->equipmentData->isEqOpened == 1) drawEqLayout();
	if (this->equipmentData->isChestOpened == 1) drawChestLayout();

	if (this->equipmentData->isEqOpened == 1) drawItemsEq(); 
	if (this->equipmentData->isChestOpened == 1) drawItemsChest();

	equipmentManagement->render();
		
}

void Equipment::drawItemsEq()
{
	for (int i = 0; i < this->Eq.size(); ++i)
		for (int j = 0; j < this->Eq[i].size(); ++j)
			if (Eq[i][j] != nullptr)
			{
				Eq[i][j]->render();
			}
}

//Draw functions
void Equipment::drawItemsChest()
{
	if (this->equipmentData->openedChest != nullptr)
		this->equipmentData->openedChest->render();
}

void Equipment::drawChestLayout()
{
	for (int i = 0; i < this->Eq.size(); ++i)
		for (int j = 1; j < this->Eq[i].size()+1; ++j)
		{
			this->BottomBarPtr->setPosition(
				this->equipmentData->FirstItemPositionChest.x + (i * this->equipmentData->SizeOfItems), 
				this->equipmentData->FirstItemPositionChest.y + j * this->equipmentData->SizeOfItems);

			this->graphicsData->window->draw(*this->BottomBarPtr);
		}
}

void Equipment::drawEqLayout()
{
	for (int i = 0; i < this->Eq.size(); ++i)
		for (int j = 1; j < this->Eq[i].size(); ++j)
		{
			this->BottomBarPtr->setPosition(
				this->equipmentData->FirstItemPositionEq.x + (i * this->equipmentData->SizeOfItems), 
				this->equipmentData->FirstItemPositionEq.y + j * this->equipmentData->SizeOfItems - (3*this->equipmentData->SizeOfItems));

			this->graphicsData->window->draw(*this->BottomBarPtr);
		}
}

void Equipment::drawBottomBarLayout()
{
	for (int i = 0; i < this->equipmentData->sizeOfEq.x; i++)
	{
		this->BottomBarPtr->setPosition(
			this->equipmentData->FirstItemPositionEq.x + (i * this->equipmentData->SizeOfItems), 
			this->equipmentData->FirstItemPositionEq.y);

		this->graphicsData->window->draw(*this->BottomBarPtr);
	}
	this->graphicsData->window->draw(*this->BottomBarChoosenPtr);

}

void Equipment::drawItemsOnBar()
{
	for (int i = 0; i < this->Eq.size(); i++)
		if (Eq[i][2] != nullptr)
			Eq[i][2]->render();
}

bool Equipment::assignCatchedItem(item* item, bool recursion)
{
	if (recursion == 0)
		lastPlaceOfPuttingEq = {};
	
	
	lastPlaceOfPuttingEq = WhereToPutItem(item, recursion); //it returns positions on Eq[][] where to put item, need to check if it is nullptr - then move item there, if there is something already need to stack it 
	
	if (lastPlaceOfPuttingEq.x != 5 and lastPlaceOfPuttingEq.y != 5)
	{
		if (Eq[lastPlaceOfPuttingEq.x][lastPlaceOfPuttingEq.y] == nullptr)
			Eq[lastPlaceOfPuttingEq.x][lastPlaceOfPuttingEq.y] = item;

		else if (Eq[lastPlaceOfPuttingEq.x][lastPlaceOfPuttingEq.y] != nullptr)
		{
			this->overMax = Eq[lastPlaceOfPuttingEq.x][lastPlaceOfPuttingEq.y]->addItemsReturn1IfOverMax(item);

			if (this->overMax)
			{
				this->overMax = 0;
				assignCatchedItem(item, 1);
			}
		}

		item->itemSprite.setOrigin(0, 0);
		item->itemSprite.setScale(1, 1); 
		
		return true;
	}
	else 
	{ 
		this->equipmentData->IDofItemsWhichCantBeTaken.insert(item->itemID); 
	} 
	return false;
}

bool Equipment::checkPossibleSpace()
{
	for (int i=0; i<Eq.size();++i)
		for (int j=0;j<Eq[0].size();++j)
			if (Eq[i][j] == nullptr) 
			{ 
				this->equipmentData->IDofItemsWhichCantBeTaken.clear(); 
				return true; 
			}
			else if (Eq[i][j]->checkIfAddable()==0)
			{
				this->equipmentData->IDofItemsWhichCantBeTaken.insert(this->Eq[i][j]->itemID);
			}
	return false;
}

sf::Vector2i Equipment::WhereToPutItem(item* Item, bool recursion)
{
	int x = 0;
	int y = 0;

	bool PossibleSearch{1};

	if (recursion)
	{
		x = lastPlaceOfPuttingEq.x+1;
		y = lastPlaceOfPuttingEq.y;

		if (y >= Eq.size())
		{
			x++;
			y = 0;
		}

		if (x >= Eq[0].size())
		{
			PossibleSearch = 0;
		}
	}

	bool foundPerf{};
	if (PossibleSearch)
	{
		for (int i = y; i < Eq[0].size(); ++i)
			for (int j = x; j < Eq.size(); ++j)
			{
				if (Eq[j][OrderOfSearch[i]] != nullptr)
				{
					if (Eq[j][OrderOfSearch[i]]->itemID == Item->itemID)
					{
						WhereToPut = { j,OrderOfSearch[i] };

						i = Eq[0].size();
						j = Eq.size();
						foundPerf = 1;
					}
				}
			}

		if (not foundPerf)
			for (int i = 0; i < Eq[0].size(); ++i)
				for (int j = 0; j < Eq.size(); ++j)
					if (Eq[j][OrderOfSearch[i]] == nullptr)
					{
						WhereToPut = { j,OrderOfSearch[i] };
						i = Eq[0].size();
						j = Eq.size();
					}
	}
	return WhereToPut;
}

//Functions
void Equipment::openingEquipment(const std::map<std::string, button*>& AllKeys)
{
	this->ableToClose = 0;
	this->ableToOpen = 0;

	if (AllKeys.at("E")->oneSignalButtonPressed())
	{
		if (this->equipmentData->isEqOpened == 1)
			this->ableToClose = 1;
		else this->ableToOpen = 1;
	}

	if (this->ableToOpen)
		this->equipmentData->isEqOpened = 1;

	if (this->ableToClose and this->equipmentManagement->ableToCloseEq()) //prevents from holding an item and closing chest at the same time 
	{
		this->equipmentData->isEqOpened = 0;
		this->equipmentData->isChestOpened = 0;
		this->equipmentData->openedChest = nullptr;
	}


	
}

void Equipment::openingChest(const std::map<std::string, button*>& AllKeys)
{
	if (this->equipmentData->isEqOpened == 0)
		if (AllKeys.at("RightMouse")->oneSignalButtonPressed()) //NEED TO CHECK IF ITS ON THE TILE MAP -> >=0 <=50/70
		{
			this->OpenedChestCoords = AllKeys.at("RightMouse")->mouseTileGet();

			if ((*Tile)[OpenedChestCoords.x][OpenedChestCoords.y] != nullptr)
			{
				if ((*Tile)[OpenedChestCoords.x][OpenedChestCoords.y]->typeOfTile == 8)
				{
					ableToOpen = 1;
					this->equipmentData->openedChest = this->Tile->at(OpenedChestCoords.x).at(OpenedChestCoords.y)->chest;
				}

				if (this->ableToOpen)
				{
					this->equipmentData->isEqOpened = 1;
					this->equipmentData->isChestOpened = 1;
				}

			}
		}
}

void Equipment::calculatePositionOfFirstItemEqAndChest()
{
	sf::Vector2f MapBorder{};

	MapBorder = { (float)this->graphicsData->window->getSize().x,(float)this->graphicsData->window->getSize().y };
	this->equipmentData->FirstItemPositionEq = { 
		(MapBorder.x / 2)-(this->equipmentData->sizeOfEq.x/2*this->equipmentData->SizeOfItems),
		MapBorder.y - this->equipmentData->Y_Offset_Bar_From_Border };
	
	this->equipmentData->FirstItemPositionChest = { 
		(MapBorder.x / 2) - (this->equipmentData->sizeOfEq.x / 2 * this->equipmentData->SizeOfItems),
		MapBorder.y - this->equipmentData->Y_Offset_Bar_From_Border - this->equipmentData->SizeOfItems * 7 };
}

void Equipment::changingSelectedItem(const std::map<std::string, button*>& AllKeys)
{
	int mem = this->equipmentData->whichItemSelected;

	if (AllKeys.at("Num1")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 0;

	if (AllKeys.at("Num2")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 1;

	if (AllKeys.at("Num3")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 2;

	if (AllKeys.at("Num4")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 3;

	if (AllKeys.at("Num5")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 4;

	if (AllKeys.at("Num6")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 5;

	if (AllKeys.at("Num7")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 6;

	if (AllKeys.at("Num8")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 7;

	if (AllKeys.at("Num9")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 8;

	if (AllKeys.at("Num0")->oneSignalButtonPressed())
		this->equipmentData->whichItemSelected = 9;


	if (mem != this->equipmentData->whichItemSelected)
		this->equipmentData->actionIsHappening = 0;

	changeBar();
}

void Equipment::puttingThrownItemToEq(ThrownItems* ThrownItem)
{
	;
}

void Equipment::updateItemsThrown(const float& dt)
{
	this->ItemsThrown->erase
	(
		std::remove_if(
			this->ItemsThrown->begin(),
			this->ItemsThrown->end(),
			[&](auto& ItemsThrown)
			{
				ItemsThrown->update(dt);

				//here need to check if there is space for picked item 
				checkPossibleSpace();
				
				if (ItemsThrown->checkIfCatched())
				{
					if (assignCatchedItem(ItemsThrown->getItem(), 0))
					{
						this->SprToDelete = &ItemsThrown->getItem()->itemSprite;
						this->itemToDeleteFound = 1;
						return true;
					}
					else return false;
				}
			}
		), ItemsThrown->end()
	);

	this->ItemsThrown->shrink_to_fit();

	if (this->itemToDeleteFound)
	{ 
		this->equipmentData->needToUpdateEq = true;
		
		this->graphicsData->ItemsThrownSprite->erase
		(
			std::remove_if(this->graphicsData->ItemsThrownSprite->begin(),
				this->graphicsData->ItemsThrownSprite->end(),
				[&](auto& ItemsSpriteThrow) { return ItemsSpriteThrow == SprToDelete; }
			), this->graphicsData->ItemsThrownSprite->end()
		);

		this->graphicsData->ItemsThrownSprite->shrink_to_fit();

		this->equipmentData->needToUpdateCameraAllSpr = 1;
		
		this->SprToDelete = nullptr;
		this->itemToDeleteFound = 0;
		this->WhereToPut={5,5};	//looks ugly but it needs to be this way
	}
}

void Equipment::changeBar()
{
	BottomBarChoosenPtr->setPosition(this->equipmentData->FirstItemPositionEq.x + (this->equipmentData->SizeOfItems * this->equipmentData->whichItemSelected), this->equipmentData->FirstItemPositionEq.y);
}

void Equipment::updatePositionOfItems()
{
	if (this->equipmentData->needToUpdateEq)
	{
		for (int i = 0; i < this->equipmentData->sizeOfEq.x; ++i)
			for (int j = 0; j < this->equipmentData->sizeOfEq.y; ++j)
				if (Eq[i][j] != nullptr)
					this->Eq[i][j]->initPositon({ i,j }, equipmentData->FirstItemPositionEq, equipmentData->SizeOfItems, 0);
	}

	if (this->equipmentData->needToUpdateChest)
	{
		for (int i = 0; i < this->equipmentData->sizeOfEq.x; ++i)
			for (int j = 0; j < this->equipmentData->sizeOfEq.y; ++j)
				if (this->equipmentData->openedChest->items[i][j] != nullptr)
					this->equipmentData->openedChest->items[i][j]->initPositon({ i,j }, equipmentData->FirstItemPositionEq, equipmentData->SizeOfItems, this->equipmentData->OffsetHeightEqAndSpacing);
	}

	this->equipmentData->needToUpdateEq = false;
	this->equipmentData->needToUpdateChest = false;
}

//Init functions
void Equipment::initGraphics()
{
	BottomBarTxtPtr->loadFromFile("Texture/Ramka.png");
	BottomBarPtr->setTexture(*this->BottomBarTxtPtr);
	BottomBarPtr->setPosition(this->equipmentData->FirstItemPositionEq.x, this->equipmentData->FirstItemPositionEq.y);

	BottomBarChoosenTxtPtr->loadFromFile("Texture/Ramka1.png");
	BottomBarChoosenPtr->setTexture(*this->BottomBarChoosenTxtPtr);
	BottomBarChoosenPtr->setPosition(this->equipmentData->FirstItemPositionEq.x, this->equipmentData->FirstItemPositionEq.y);

}

void Equipment::initEqAndBar()
{
	//std::vector<std::vector<int>> twoDVector(rows, std::vector<int>(columns, initialValue));
	this->Eq.resize(this->equipmentData->sizeOfEq.x, std::vector<item*>(this->equipmentData->sizeOfEq.y, nullptr));

	this->Eq[0][2] = new itemHoe(this->graphicsData, this->equipmentData, "Dziabka", Tile);

	this->Eq[1][2] = new itemPickaxe(this->graphicsData, this->equipmentData, "Kilof", Tile);

	this->Eq[2][2] = new itemWateringCan(this->graphicsData, this->equipmentData, "Konewka", Tile);

	this->Eq[3][2] = new itemAxe(this->graphicsData, this->equipmentData, "Siekiera", Tile);

	this->Eq[4][2] = new itemSword(this->graphicsData, this->equipmentData, "Miecz", Tile);

	this->Eq[5][2] = new itemShovel(this->graphicsData, this->equipmentData, "Lopata", Tile);

	this->Eq[2][1] = new item(this->graphicsData, this->equipmentData, "StoneEq", Tile);
	this->Eq[3][1] = new item(this->graphicsData, this->equipmentData, "StoneEq", Tile);
	this->Eq[0][0] = new item(this->graphicsData, this->equipmentData, "StoneEq", Tile);
	this->Eq[1][0] = new item(this->graphicsData, this->equipmentData, "StoneEq", Tile);
	this->Eq[3][1]->changeNumberOfItems(6);
	this->Eq[0][0]->changeNumberOfItems(998);
	this->Eq[1][0]->changeNumberOfItems(998);

	this->Eq[4][0] = new item(this->graphicsData, this->equipmentData, "WoodEq", Tile);
	this->Eq[4][0]->changeNumberOfItems(998);

	for (int i=0;i<Eq.size();++i)
		for (int j = 0; j < Eq[0].size(); ++j)
			if (Eq[i][j]==nullptr)
				this->Eq[i][j] = new itemHoe(this->graphicsData, this->equipmentData, "Dziabka", Tile);
}

