#include "EquipmentManagement.h"

EquipmentManagement::EquipmentManagement(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<item*>>* Eq, std::vector<ThrownItems*>* ItemsThrown, ThrownItems* ItemsOnTheGround)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->Eq = Eq;
	this->ItemsThrown = ItemsThrown;
	this->factoryOfItems.init(graphicsData);
	this->ItemsOnTheGround = ItemsOnTheGround;

	this->OffsetHeightEqAndSpacing = HeightOfEqPlusChest - equipmentData->sizeOfEq.y; //7-3 = 4

}

void EquipmentManagement::update(const std::map<std::string, button*>& AllKeys)
{
	if (not(AllKeys.at("LShift")->isButtonPressed()) and AllKeys.at("LeftMouse")->oneSignalButtonPressed() and itemGrabbed == nullptr and itemTakenThisFrame == 0) //DONE
		catchingItem(AllKeys);

	if (AllKeys.at("LShift")->isButtonPressed() and AllKeys.at("LeftMouse")->oneSignalButtonPressed() and itemGrabbed == nullptr and itemTakenThisFrame == 0 and this->equipmentData->isChestOpened) //DONE
		sendingItemToChest(AllKeys);

	if (AllKeys.at("RightMouse")->oneSignalButtonPressed() and itemGrabbed == nullptr)
		catchingOneItem(AllKeys);

	if (AllKeys.at("RightMouse")->oneSignalButtonPressed() and itemGrabbed != nullptr and itemTakenThisFrame == 0)
		rightClickAddingItems(AllKeys);

	if (itemGrabbed != nullptr) //DONE
		movingItemWhileClicked(AllKeys);

	if (AllKeys.at("LeftMouse")->oneSignalButtonPressed() and itemGrabbed != nullptr and itemTakenThisFrame == 0) //DONE 
		puttingOffItem(AllKeys);

	this->itemTakenThisFrame = 0;

}

void EquipmentManagement::render()
{
	if (this->itemGrabbed != nullptr)
		this->itemGrabbed->render(); //its doubled - render in eq/chest render function and here
}

bool EquipmentManagement::ableToCloseEq()
{
	if (itemGrabbed==nullptr) return true;
	return false;
}

bool EquipmentManagement::isMouseInEqLayout()
{
	if (this->equipmentData->eqPosNew.x >= 0
		and this->equipmentData->eqPosNew.x < this->equipmentData->sizeOfEq.x
		and ((this->equipmentData->eqPosNew.y >= 0 and this->equipmentData->eqPosNew.y < this->equipmentData->sizeOfEq.y and this->equipmentData->isChestOpened)
			or (this->equipmentData->eqPosNew.y >= (this->HeightOfEqPlusChest - this->equipmentData->sizeOfEq.y) and this->equipmentData->eqPosNew.y < this->HeightOfEqPlusChest)))
		return true;
	else return false;
}

void EquipmentManagement::assigningGrabbedItem(int OffsetHeightEqAndSpacing)
{
	if (catchedOneItem == 0)
	{
		if (takenFromEq)
			this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - EquipmentManagement::OffsetHeightEqAndSpacing) = holder;
		else
			this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y] = holder;
	}

	//If slot wasnt empty
	if (this->holder != nullptr)
	{
		if (holder->itemID == itemGrabbed->itemID and holder != itemGrabbed)
		{
			stackingItems();
		}
	}
}

void EquipmentManagement::stackingItems()
{
	//if over max = 1 i need to do normal things like its not inside stacking func

	this->overMax = itemGrabbed->addItemsReturn1IfOverMax(holder);

	if (catchedOneItem == 0)
		if (this->overMax == false)
		{
			if (takenFromEq)
				this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - EquipmentManagement::OffsetHeightEqAndSpacing) = nullptr;
			else
				this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y] = nullptr;
		}
}

void EquipmentManagement::catchingItem(const std::map<std::string, button*>& AllKeys)
{
	this->equipmentData->eqPos.x = (AllKeys.at("LeftMouse")->mousePosGet().x - (int)this->equipmentData->FirstItemPositionEq.x) / this->equipmentData->SizeOfItems;
	this->equipmentData->eqPos.y = ((AllKeys.at("LeftMouse")->mousePosGet().y - (int)this->equipmentData->FirstItemPositionEq.y + (this->HeightOfEqPlusChest * this->equipmentData->SizeOfItems)) / this->equipmentData->SizeOfItems) - 1;

	//y -> 0-2 chest --- 3 spacing --- 4-6 eq
	
	if (this->itemGrabbed == nullptr)
		if (this->equipmentData->eqPos.x >= 0 and this->equipmentData->eqPos.x < this->equipmentData->sizeOfEq.x)
			if (this->equipmentData->eqPos.y >= 0 and this->equipmentData->eqPos.y < this->equipmentData->sizeOfEq.y and this->equipmentData->isChestOpened)																	//Chest area
			{
				if (this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y] != nullptr)
				{
					this->itemGrabbed = this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y];
					this->takenFromEq = 0;
					this->itemTakenThisFrame = 1;
				}
			}
			else if (this->equipmentData->eqPos.y >= (this->HeightOfEqPlusChest - this->equipmentData->sizeOfEq.y) and this->equipmentData->eqPos.y < this->HeightOfEqPlusChest)		//Eq area
			{
				if (this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing) != nullptr)
				{
					this->itemGrabbed = Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing);
					this->takenFromEq = 1;
					this->itemTakenThisFrame = 1;
				}
			}
}

void EquipmentManagement::movingItemWhileClicked(const std::map<std::string, button*>& AllKeys)
{
	itemGrabbed->itemSprite.setPosition(AllKeys.at("LeftMouse")->mousePosGet().x - TilesOnMap::GetSizeOfTile(), AllKeys.at("LeftMouse")->mousePosGet().y - TilesOnMap::GetSizeOfTile());
}

void EquipmentManagement::puttingOffItem(const std::map<std::string, button*>& AllKeys)
{
	//Need to add stacking the same item in the future

	//New positions
	this->equipmentData->eqPosNew.x = std::floor((float)(AllKeys.at("LeftMouse")->mousePosGet().x - (int)this->equipmentData->FirstItemPositionEq.x) / (float)this->equipmentData->SizeOfItems);
	this->equipmentData->eqPosNew.y = ((AllKeys.at("LeftMouse")->mousePosGet().y - (int)this->equipmentData->FirstItemPositionEq.y + (this->HeightOfEqPlusChest * this->equipmentData->SizeOfItems)) / this->equipmentData->SizeOfItems) - 1;

	this->holder = nullptr;

	//Checking if mouse pos in on eq / chest
	if (isMouseInEqLayout())
	{
		if (this->equipmentData->eqPosNew.y >= 0 and this->equipmentData->eqPosNew.y < this->equipmentData->sizeOfEq.y and this->equipmentData->isChestOpened) //Chest area
		{
			if (this->equipmentData->openedChest->items[this->equipmentData->eqPosNew.x][this->equipmentData->eqPosNew.y] != nullptr)
				this->holder = this->equipmentData->openedChest->items[this->equipmentData->eqPosNew.x][this->equipmentData->eqPosNew.y];


			this->equipmentData->openedChest->items[this->equipmentData->eqPosNew.x][this->equipmentData->eqPosNew.y] = this->itemGrabbed;

			assigningGrabbedItem(0);

		}
		else if (this->equipmentData->eqPosNew.y >= (this->HeightOfEqPlusChest - this->equipmentData->sizeOfEq.y) and this->equipmentData->eqPosNew.y < this->HeightOfEqPlusChest) //Eq area
		{
			if (this->Eq->at(this->equipmentData->eqPosNew.x).at(this->equipmentData->eqPosNew.y - this->OffsetHeightEqAndSpacing) != nullptr)
				this->holder = this->Eq->at(this->equipmentData->eqPosNew.x).at(this->equipmentData->eqPosNew.y - this->OffsetHeightEqAndSpacing);

			this->Eq->at(this->equipmentData->eqPosNew.x).at(this->equipmentData->eqPosNew.y - this->OffsetHeightEqAndSpacing) = this->itemGrabbed;


			assigningGrabbedItem(this->OffsetHeightEqAndSpacing);

		}

	}
	else
	{
		throwItem(itemGrabbed);
		if (catchedOneItem == 0)
		{
			if (takenFromEq)
				this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - EquipmentManagement::OffsetHeightEqAndSpacing) = nullptr;
			else
				this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y] = nullptr;
		}
	}

	this->holder = nullptr;
	this->itemGrabbed = nullptr;
	this->takenFromEq = 0;
	this->catchedOneItem = 0;

	this->equipmentData->needToUpdateEq = true;

	if (this->equipmentData->isChestOpened)
		this->equipmentData->needToUpdateChest = true;
}

void EquipmentManagement::sendingItemToChest(const std::map<std::string, button*>& AllKeys)
{
	std::cout << "XD\n";
}

void EquipmentManagement::catchingOneItem(const std::map<std::string, button*>& AllKeys)
{
	this->equipmentData->eqPos.x = (AllKeys.at("LeftMouse")->mousePosGet().x - (int)this->equipmentData->FirstItemPositionEq.x) / this->equipmentData->SizeOfItems;
	this->equipmentData->eqPos.y = ((AllKeys.at("LeftMouse")->mousePosGet().y - (int)this->equipmentData->FirstItemPositionEq.y + (this->HeightOfEqPlusChest * this->equipmentData->SizeOfItems)) / this->equipmentData->SizeOfItems) - 1;

	//After catching 
	

	if (this->itemGrabbed == nullptr)
		if (this->equipmentData->eqPos.x >= 0 and this->equipmentData->eqPos.x < this->equipmentData->sizeOfEq.x)
			if (this->equipmentData->eqPos.y >= 0 and this->equipmentData->eqPos.y < this->equipmentData->sizeOfEq.y and this->equipmentData->isChestOpened)																	//Chest area
			{
				if (this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y] != nullptr)
				{
					if (this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y]->getNumberOfItems() == 1)
						catchingItem(AllKeys);
					else
					{
						this->itemGrabbed = factoryOfItems.creatorOfItemBasedOnExample(this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y]);
						*this->itemGrabbed = *this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y];
						this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y]->substrFromThisItem(1);
						this->itemGrabbed->changeNumberOfItems(1);
						this->takenFromEq = 0;
						this->catchedOneItem = 1; //Need to reset it while putting item 
						this->itemTakenThisFrame = 1;
					}
				}
			}
			else if (this->equipmentData->eqPos.y >= (this->HeightOfEqPlusChest - this->equipmentData->sizeOfEq.y) and this->equipmentData->eqPos.y < this->HeightOfEqPlusChest)		//Eq area
			{
				if (this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing) != nullptr)
				{
					if (this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing)->getNumberOfItems() == 1)
						catchingItem(AllKeys);
					else
					{
						this->itemGrabbed = factoryOfItems.creatorOfItemBasedOnExample(Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing));
						*this->itemGrabbed = *Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing);
						Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - this->OffsetHeightEqAndSpacing)->substrFromThisItem(1);
						this->itemGrabbed->changeNumberOfItems(1);
						this->takenFromEq = 1;
						this->catchedOneItem = 1; //Need to reset it while putting item 
						this->itemTakenThisFrame = 1;
					}
				}
			}
}

void EquipmentManagement::rightClickAddingItems(const std::map<std::string, button*>& AllKeys)
{
	this->equipmentData->eqPosNew.x = std::floor((float)(AllKeys.at("LeftMouse")->mousePosGet().x - (int)this->equipmentData->FirstItemPositionEq.x) / (float)this->equipmentData->SizeOfItems);
	this->equipmentData->eqPosNew.y = ((AllKeys.at("LeftMouse")->mousePosGet().y - (int)this->equipmentData->FirstItemPositionEq.y + (this->HeightOfEqPlusChest * this->equipmentData->SizeOfItems)) / this->equipmentData->SizeOfItems) - 1;

	if (isMouseInEqLayout())
	{
		if (this->equipmentData->eqPosNew.y >= 0 and this->equipmentData->eqPosNew.y < this->equipmentData->sizeOfEq.y) //Chest area
		{
			if (this->equipmentData->openedChest->items[this->equipmentData->eqPosNew.x][this->equipmentData->eqPosNew.y] != nullptr)
			{
				if (this->equipmentData->openedChest->items[this->equipmentData->eqPosNew.x][this->equipmentData->eqPosNew.y]->itemID == itemGrabbed->itemID)
				{
					itemGrabbed->addToThisItem(1);
					this->equipmentData->openedChest->items[this->equipmentData->eqPosNew.x][this->equipmentData->eqPosNew.y]->substrFromThisItem(1);
					if (this->equipmentData->openedChest->items[this->equipmentData->eqPosNew.x][this->equipmentData->eqPosNew.y]->getNumberOfItems() == 0)
						this->equipmentData->openedChest->items[this->equipmentData->eqPosNew.x][this->equipmentData->eqPosNew.y] = nullptr;
				}
			}
			else
			{
				if (itemGrabbed->getNumberOfItems() > 1)
				{
					this->itemGrabbed->substrFromThisItem(1);
					this->equipmentData->openedChest->items[this->equipmentData->eqPosNew.x][this->equipmentData->eqPosNew.y] = factoryOfItems.creatorOfItemBasedOnExample(itemGrabbed);
					*this->equipmentData->openedChest->items[this->equipmentData->eqPosNew.x][this->equipmentData->eqPosNew.y] = *itemGrabbed;
				}
				else
				{
					std::cout << "tutereeeej\n";
					this->equipmentData->openedChest->items[this->equipmentData->eqPosNew.x][this->equipmentData->eqPosNew.y] = itemGrabbed;
					itemGrabbed = nullptr;

					if (takenFromEq)
						this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - EquipmentManagement::OffsetHeightEqAndSpacing) = holder;
					else
						this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y] = holder;
				}
				this->equipmentData->needToUpdateChest = true;
			}


		}
		else if (this->equipmentData->eqPosNew.y >= (this->HeightOfEqPlusChest - this->equipmentData->sizeOfEq.y) and this->equipmentData->eqPosNew.y < this->HeightOfEqPlusChest) //Eq area
		{
			if (this->Eq->at(this->equipmentData->eqPosNew.x).at(this->equipmentData->eqPosNew.y - this->OffsetHeightEqAndSpacing) != nullptr)
			{
				if (this->Eq->at(this->equipmentData->eqPosNew.x).at(this->equipmentData->eqPosNew.y - this->OffsetHeightEqAndSpacing)->itemID == itemGrabbed->itemID)
				{
					itemGrabbed->addToThisItem(1);
					this->Eq->at(this->equipmentData->eqPosNew.x).at(this->equipmentData->eqPosNew.y - this->OffsetHeightEqAndSpacing)->substrFromThisItem(1);
					if (this->Eq->at(this->equipmentData->eqPosNew.x).at(this->equipmentData->eqPosNew.y - this->OffsetHeightEqAndSpacing)->getNumberOfItems() == 0)
						this->Eq->at(this->equipmentData->eqPosNew.x).at(this->equipmentData->eqPosNew.y - this->OffsetHeightEqAndSpacing) = nullptr;
				}
			}
			else
			{
				if (itemGrabbed->getNumberOfItems() > 1)
				{
					this->itemGrabbed->substrFromThisItem(1);
					this->Eq->at(this->equipmentData->eqPosNew.x).at(this->equipmentData->eqPosNew.y - this->OffsetHeightEqAndSpacing) = factoryOfItems.creatorOfItemBasedOnExample(itemGrabbed);
					*this->Eq->at(this->equipmentData->eqPosNew.x).at(this->equipmentData->eqPosNew.y - this->OffsetHeightEqAndSpacing) = *itemGrabbed;
				}
				else
				{
					this->Eq->at(this->equipmentData->eqPosNew.x).at(this->equipmentData->eqPosNew.y - this->OffsetHeightEqAndSpacing) = itemGrabbed;
					itemGrabbed = nullptr;

					if (takenFromEq)
						this->Eq->at(this->equipmentData->eqPos.x).at(this->equipmentData->eqPos.y - EquipmentManagement::OffsetHeightEqAndSpacing) = holder;
					else
						this->equipmentData->openedChest->items[this->equipmentData->eqPos.x][this->equipmentData->eqPos.y] = holder;
				}
				this->equipmentData->needToUpdateEq = true;
			}
		}
	}
}

void EquipmentManagement::throwItem(item* item)
{
	//this->ItemsThrown->push_back(new ThrownItems(this->graphicsData, this->equipmentData, item, this->ItemsThrown));
	this->ItemsOnTheGround->insertItem(item);
}
