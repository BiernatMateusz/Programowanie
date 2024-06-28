#ifndef THROWNITEMS_H
#define THROWNITEMS_H

#include <iostream>
#include "StructuresOfData.h"
#include "item.h"
#include <cmath>


#define M_PI 3.14159265358979323846

class ThrownItems
{
private:
	std::string direction{};
	item* Item;
	const int range{ 100 };
	const double gravity{ 200 };
	const float v0 = 200;
	float offsetY{ 30 };
	float additionalOffset{};
	sf::Vector2f distanceFlied{};
	std::vector<ThrownItems*>* ItemsThrown{};
	bool firstCycle{1};

	GraphicsData* graphicsData;
	EquipmentData* equipmentData;

	bool destinationReached{};

	sf::Vector2f initialPosition{};
	sf::Vector2f destinationOfItem{};
	float distance{};
	const float distanceValue{80};
	const float minDistanceToCatchItem{ 10 };
	const float maxDistanceToCatchItem{ 100 };
	sf::Vector2f SpeedOfFlyingItem{};
	sf::Vector2f distanceToGo{0,0};

	sf::Vector2f positions{};
	float timePassed{};
	const float timeToCatch{3};
	void xyValueOfFly(const float& dt);
	bool catchedItem{};
	
	std::vector<std::vector<item*>>*Eq{};
	std::vector<ThrownItems*> ItemsThrownVec{};
	bool checkPossibleSpace();
	bool assignCatchedItem(item* item, bool recursion);
	bool overMax{};
	sf::Sprite* SprToDelete{};
	bool itemToDeleteFound{};
	sf::Vector2i lastPlaceOfPuttingEq{};
	sf::Vector2i WhereToPut{ 5,5 };
	std::vector<int> OrderOfSearch{ 2,0,1 };

	sf::Vector2i WhereToPutItem(item* Item, bool recursion);


	sf::Vector2f distanceToPlayer{};
	bool checkDistance();



public:
	//Constructors
	ThrownItems(GraphicsData* graphicsData, EquipmentData* equipmentData);

	ThrownItems(GraphicsData* graphicsData, EquipmentData* equipmentData, item* item, std::vector<ThrownItems*>* ThrownItems);

	//ThrownItems(Equipment* Wq);
	void setItemDestination();
	void setItemParameters();

	void getAndChangeDestinationOfItem(sf::Vector2f MoveValues);
	bool checkIfCatched();

	void update(const float& dt);

	void update2(const float& dt);
	void update(ThrownItems* itemek, const float& dt);
	void initEqPtr(std::vector<std::vector<item*>>*Eq);
	void insertItem(item* itemToAdd);

	void pickUp(ThrownItems* ThrownItem);

	void updateItemsThrownSpriteVec(std::vector<ThrownItems*>* ThrItems);
	void updateItemsThrownSpriteVec();
	item* getItem();
	sf::Sprite* getSprite();


};

#endif 