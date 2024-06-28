#ifndef EQUIPMENTMANAGEMENT_H
#define EQUIPMENTMANAGEMENT_H

#include "StructuresOfData.h"
#include "ThrownItems.h"
#include "ItemConstructor.h"
#include "ThrownItems.h"

class EquipmentManagement
{
public:
	EquipmentManagement(GraphicsData* graphicsData, EquipmentData* equipmentData, std::vector<std::vector<item*>>*Eq, std::vector<ThrownItems*>* ItemsThrown, ThrownItems* ItemsOnTheGround);

	void update(const std::map<std::string, button*>& AllKeys);
	void render();

	bool ableToCloseEq();

	bool isMouseInEqLayout();
	void assigningGrabbedItem(int OffsetHeightEqAndSpacing);
	void stackingItems();

	void catchingItem(const std::map<std::string, button*>& AllKeys);
	void movingItemWhileClicked(const std::map<std::string, button*>& AllKeys);
	void puttingOffItem(const std::map<std::string, button*>& AllKeys);
	void sendingItemToChest(const std::map<std::string, button*>& AllKeys);
	void catchingOneItem(const std::map<std::string, button*>& AllKeys);
	void rightClickAddingItems(const std::map<std::string, button*>& AllKeys);
	void throwItem(item* item);

private:
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;

	std::vector<std::vector<item*>>*Eq{};
	std::vector<ThrownItems*>* ItemsThrown{};
	ThrownItems* ItemsOnTheGround{};

	item* itemGrabbed = nullptr;
	item* holder = nullptr;

	//Factory Items
	ItemConstructor factoryOfItems;

	bool overMax{};
	bool itemTakenThisFrame{};
	bool catchedOneItem{};
	const int HeightOfEqPlusChest = 7; //eq->3 , chest->3 , spacing between->1
	sf::Vector2i OpenedChestCoords{};
	bool takenFromEq = 0;
	int OffsetHeightEqAndSpacing;
};

#endif // !EQUIPMENTMANAGEMENT_H
