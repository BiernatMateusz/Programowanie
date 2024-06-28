#include "ThrownItems.h"

ThrownItems::ThrownItems(GraphicsData* graphicsData, EquipmentData* equipmentData)
{
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
}

ThrownItems::ThrownItems(GraphicsData* graphicsData,EquipmentData* equipmentData, item* item, std::vector<ThrownItems*>*ThrownItems)
{
	this->ItemsThrown = ThrownItems;
	this->graphicsData = graphicsData;
	this->equipmentData = equipmentData;
	this->Item = item;
	this->direction = this->graphicsData->directionOfPlayer;

	setItemParameters();
	setItemDestination();

}

void ThrownItems::xyValueOfFly(const float& dt)
{
	timePassed += dt;
	positions.x = v0 * timePassed * cos(30 * M_PI);
	positions.y = v0 * timePassed * sin(30 * M_PI) - (gravity*timePassed*timePassed)/2;
	positions.y -= positions.y / 2;
	positions.y *= -1;
	positions.y += positions.y * 2;

}

sf::Vector2i ThrownItems::WhereToPutItem(item* Item, bool recursion)
{
	int x = 0;
	int y = 0;

	bool PossibleSearch{ 1 };

	if (recursion)
	{
		x = lastPlaceOfPuttingEq.x + 1;
		y = lastPlaceOfPuttingEq.y;

		if (y >= Eq->size())
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
			for (int j = x; j < Eq->size(); ++j)
			{
				if (Eq->at(j).at(OrderOfSearch[i]) != nullptr)
				{
					if (Eq->at(j).at(OrderOfSearch[i])->itemID == Item->itemID)
					{
						WhereToPut = { j,OrderOfSearch[i] };

						i = Eq[0].size();
						j = Eq->size();
						foundPerf = 1;
					}
				}
			}

		if (not foundPerf)
			for (int i = 0; i < Eq[0].size(); ++i)
				for (int j = 0; j < Eq->size(); ++j)
					if (Eq->at(j).at(OrderOfSearch[i]) == nullptr)
					{
						WhereToPut = { j,OrderOfSearch[i] };
						i = Eq[0].size();
						j = Eq->size();
					}
	}
	return WhereToPut;
}

bool ThrownItems::checkDistance()
{
	this->distanceToPlayer.x = this->Item->itemSprite.getPosition().x - this->graphicsData->player->getPosition().x;
	this->distanceToPlayer.y = this->Item->itemSprite.getPosition().y - this->graphicsData->player->getPosition().y;

	this->distance = sqrt(pow(distanceToPlayer.x, 2) + pow(distanceToPlayer.y, 2));

	if (this->distance <= this->minDistanceToCatchItem)
	{
		catchedItem = 1;
		return false;
	}

	if (this->distance < this->maxDistanceToCatchItem)
	{
		return true;
	}
	return false;

}

void ThrownItems::update(const float& dt)
{ 
	if (firstCycle) 
	{ 
		updateItemsThrownSpriteVec(this->ItemsThrown); 
		firstCycle = 0;
	}

	auto pos = this->equipmentData->IDofItemsWhichCantBeTaken.find(this->Item->itemID);
	
	if (pos == this->equipmentData->IDofItemsWhichCantBeTaken.end())
	{
		//std::cout << "ruszam\n";
		if (destinationReached == false)
		{
			xyValueOfFly(dt);
			if (this->direction == "right")
			{
				distanceFlied += dt * positions;

				if (distanceFlied.y >= offsetY)
					positions.y = this->initialPosition.y - this->destinationOfItem.y;
			}
			else if (this->direction == "left")
			{
				distanceFlied += dt * positions;
				positions.x = -positions.x;

				if (distanceFlied.y >= offsetY)
					positions.y = this->initialPosition.y - this->destinationOfItem.y;
			}
			else if (this->direction == "top")
			{
				positions.y = -positions.x;
				positions.x = 0;

				distanceFlied -= dt * positions;
				std::cout << distanceFlied.y << "\n";

			}
			else if (this->direction == "bot")
			{
				positions.y = positions.x;
				positions.x = 0;

				distanceFlied += dt * positions;
			}

			this->Item->itemSprite.move(dt * this->positions.x, dt * positions.y);

			if (direction == "top" or direction == "bot")
			{
				if (direction == "top")
					additionalOffset = offsetY;

				if (distanceFlied.y >= distanceValue - additionalOffset)
					destinationReached = 1;
			}
			else
				if (distanceFlied.x >= distanceValue)
					destinationReached = 1;

			//threwn items needs to detect collision
			//items need to follow player when near enough (3 seconds after dropping from eq)
			//take it to 1st empty slot in eq
		}
		else
		{
			timePassed += dt;
		}

		if (timePassed > this->timeToCatch)
			if (checkDistance())
			{
				SpeedOfFlyingItem.x = -std::copysign(this->maxDistanceToCatchItem * 1.5 * dt, this->distanceToPlayer.x);
				SpeedOfFlyingItem.y = -std::copysign(this->maxDistanceToCatchItem * 1.5 * dt, this->distanceToPlayer.y);
				this->Item->itemSprite.move(SpeedOfFlyingItem);
			}
	}
	else destinationReached = 0;

}



void ThrownItems::updateItemsThrownSpriteVec(std::vector<ThrownItems*>* ThrItems)
{
	this->graphicsData->ItemsThrownSprite->clear();
	for (auto* elem : *ThrItems)
		this->graphicsData->ItemsThrownSprite->push_back(&elem->Item->itemSprite);
	this->equipmentData->needToUpdateCameraAllSpr = 1;
}

void ThrownItems::updateItemsThrownSpriteVec()
{
	this->graphicsData->ItemsThrownSprite->clear();
	for (auto* elem : ItemsThrownVec)
		this->graphicsData->ItemsThrownSprite->push_back(&elem->Item->itemSprite);
	this->equipmentData->needToUpdateCameraAllSpr = 1;
}

item* ThrownItems::getItem()
{
	return this->Item;
}

sf::Sprite* ThrownItems::getSprite()
{
	return &this->Item->itemSprite;
}

void ThrownItems::getAndChangeDestinationOfItem(sf::Vector2f MoveValues)
{
	this->destinationOfItem.x += MoveValues.x;
	this->destinationOfItem.y += MoveValues.y;
}

bool ThrownItems::checkIfCatched()
{
	//std::cout << "Wielkosc setu " << IDofItemsWhichCantBeTaken->size() << "\n";

	if (this->catchedItem) 
	{
		auto pos = this->equipmentData->IDofItemsWhichCantBeTaken.find(this->Item->itemID);
		
		if (pos != this->equipmentData->IDofItemsWhichCantBeTaken.end())
		{
			this->catchedItem = 0;
			//std::cout << "znalezione\n";
		}
		else
		{
			//this->catchedItem = 0;
			//std::cout << "nie znalezione\n";
		}
	}
	return this->catchedItem;
}

void ThrownItems::pickUp(ThrownItems* ThrownItem)
{
	ThrownItem->Item->itemSprite.setScale(1,1);
	ThrownItem->Item->itemSprite.setOrigin(0, 0);
}

void ThrownItems::setItemDestination()
{
	if (this->direction == "right")
		this->distanceToGo = {this->distanceValue,0};
	else if (this->direction=="left")
		this->distanceToGo = { -this->distanceValue,0 };
	else if (this->direction == "top")
		this->distanceToGo = { 0,-this->distanceValue };
	else if (this->direction == "bot")
		this->distanceToGo = { 0,this->distanceValue };


	this->destinationOfItem = { this->graphicsData->player->getPosition().x+this->distanceToGo.x, this->graphicsData->player->getPosition().y + this->distanceToGo.y};
}

void ThrownItems::setItemParameters()
{
	this->Item->itemSprite.setScale(this->equipmentData->scaleOfThrownItems);
	this->Item->itemSprite.setOrigin(10, 70);

	if (this->direction == "bot")
		offsetY = 0;

	this->Item->itemSprite.setPosition({ this->graphicsData->player->getPosition().x,this->graphicsData->player->getPosition().y - offsetY });
	this->initialPosition = this->Item->itemSprite.getPosition();
}

void ThrownItems::update(ThrownItems* itemek, const float& dt)
{
	
	if (firstCycle)
	{
		updateItemsThrownSpriteVec();
		firstCycle = 0;
	}

	auto pos = this->equipmentData->IDofItemsWhichCantBeTaken.find(this->Item->itemID);
	

	if (pos == this->equipmentData->IDofItemsWhichCantBeTaken.end())
	{
		//std::cout << "ruszam\n";
		if (destinationReached == false)
		{
			xyValueOfFly(dt);
			if (this->direction == "right")
			{
				distanceFlied += dt * positions;

				if (distanceFlied.y >= offsetY)
					positions.y = this->initialPosition.y - this->destinationOfItem.y;
			}
			else if (this->direction == "left")
			{
				distanceFlied += dt * positions;
				positions.x = -positions.x;

				if (distanceFlied.y >= offsetY)
					positions.y = this->initialPosition.y - this->destinationOfItem.y;
			}
			else if (this->direction == "top")
			{
				positions.y = -positions.x;
				positions.x = 0;

				distanceFlied -= dt * positions;
				std::cout << distanceFlied.y << "\n";

			}
			else if (this->direction == "bot")
			{
				positions.y = positions.x;
				positions.x = 0;

				distanceFlied += dt * positions;
			}

			//itemek->Item->itemSprite.move(dt * this->positions.x, dt * positions.y); //ERROR
			this->Item->itemSprite.move(dt * this->positions.x, dt * positions.y); //ERROR

			if (direction == "top" or direction == "bot")
			{
				if (direction == "top")
					additionalOffset = offsetY;

				if (distanceFlied.y >= distanceValue - additionalOffset)
					destinationReached = 1;
			}
			else
				if (distanceFlied.x >= distanceValue)
					destinationReached = 1;

			//threwn items needs to detect collision
			//items need to follow player when near enough (3 seconds after dropping from eq)
			//take it to 1st empty slot in eq
		}
		else
		{
			timePassed += dt;
		}

		if (timePassed > this->timeToCatch)
			if (checkDistance())
			{
				SpeedOfFlyingItem.x = -std::copysign(this->maxDistanceToCatchItem * 1.5 * dt, this->distanceToPlayer.x);
				SpeedOfFlyingItem.y = -std::copysign(this->maxDistanceToCatchItem * 1.5 * dt, this->distanceToPlayer.y);
				//itemek->Item->itemSprite.move(SpeedOfFlyingItem); //ERROR
				this->Item->itemSprite.move(SpeedOfFlyingItem); //ERROR
			}
	}
	else destinationReached = 0;

}

void ThrownItems::initEqPtr(std::vector<std::vector<item*>>* Eq)
{
	this->Eq = Eq;
}

void ThrownItems::insertItem(item* itemToAdd)
{
	this->ItemsThrownVec.push_back(new ThrownItems(this->graphicsData, this->equipmentData, itemToAdd, this->ItemsThrown));
}

bool ThrownItems::checkPossibleSpace()
{
	for (int i = 0; i < Eq->size(); ++i)
		for (int j = 0; j < Eq[0].size(); ++j)
			if (Eq->at(i).at(j) == nullptr)
			{
				this->equipmentData->IDofItemsWhichCantBeTaken.clear();
				return true;
			}
			else if (Eq->at(i).at(j)->checkIfAddable() == 0)
			{
				this->equipmentData->IDofItemsWhichCantBeTaken.insert(this->Eq->at(i).at(j)->itemID);
			}
	return false;
}

bool ThrownItems::assignCatchedItem(item* item, bool recursion)
{
	if (recursion == 0)
		lastPlaceOfPuttingEq = {};


	lastPlaceOfPuttingEq = WhereToPutItem(item, recursion); //it returns positions on Eq[][] where to put item, need to check if it is nullptr - then move item there, if there is something already need to stack it 

	if (lastPlaceOfPuttingEq.x != 5 and lastPlaceOfPuttingEq.y != 5)
	{
		if (Eq->at(lastPlaceOfPuttingEq.x).at(lastPlaceOfPuttingEq.y) == nullptr)
			Eq->at(lastPlaceOfPuttingEq.x).at(lastPlaceOfPuttingEq.y) = item;

		else if (Eq->at(lastPlaceOfPuttingEq.x).at(lastPlaceOfPuttingEq.y) != nullptr)
		{
			this->overMax = Eq->at(lastPlaceOfPuttingEq.x).at(lastPlaceOfPuttingEq.y)->addItemsReturn1IfOverMax(item);

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

void ThrownItems::update2(const float& dt)
{
	std::cout << "vecsize: "<< ItemsThrownVec.size()<<"przed" << "\n";


	if (ItemsThrownVec.size() > 0)
	{
		this->ItemsThrownVec.erase
		(
			std::remove_if(
				this->ItemsThrownVec.begin(),
				this->ItemsThrownVec.end(),
				[&](auto& ItemsThrownVec)
				{
					update(ItemsThrownVec, dt);
					//here need to check if there is space for picked item 
					checkPossibleSpace();

					if (checkIfCatched())
					{
						if (assignCatchedItem(ItemsThrownVec->getItem(), 0))
						{
							this->SprToDelete = &ItemsThrownVec->getItem()->itemSprite;
							this->itemToDeleteFound = 1;
							return true;
						}
						else return false;
					}
				}
			), ItemsThrownVec.end()
					);

		this->ItemsThrownVec.shrink_to_fit();
	}

	

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
		this->WhereToPut = { 5,5 };	//looks ugly but it needs to be this way
	}
}

	