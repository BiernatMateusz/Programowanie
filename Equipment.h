#ifndef EQUIPMENTh
#define EQUIPMENTh

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "StructuresOfData.h"
#include <iostream>

#include "ItemConstructor.h"

#include "Camera.h"
#include "ThrownItems.h"

#include "EquipmentManagement.h"

class Equipment
{
private:
	//Variables
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;
	std::vector<std::vector<TilesOnMap*>>* Tile;

	//EquipmentManagementClass
	EquipmentManagement* equipmentManagement;

	//ThrownItemsClass
	ThrownItems* ItemsOnTheGround{};

	//Bottom bar
	sf::Sprite* BottomBarPtr;
	sf::Texture* BottomBarTxtPtr;
	sf::Sprite* BottomBarChoosenPtr;
	sf::Texture* BottomBarChoosenTxtPtr;

	//All eq
	std::vector<std::vector<item*>>Eq{};

	std::vector<ThrownItems*>* ItemsThrown;
	ThrownItems* itemsOnTheGround;
	sf::Sprite* SprToDelete{};
	bool itemToDeleteFound{};

	bool ableToClose{};
	bool ableToOpen{};
	sf::Vector2i OpenedChestCoords{};

	bool overMax{};
	
	sf::Vector2i lastPlaceOfPuttingEq{};
	sf::Vector2i WhereToPut{ 5,5 };

	//Additional functions
	void changeBar();
	void updateKeybinds(const std::map<std::string, button*>& AllKeys);
	void initGraphics();
	void calculatePositionOfFirstItemEqAndChest();

	void initEqAndBar();
	void drawItemsEq();
	void drawItemsChest();
	void drawChestLayout();
	void drawEqLayout();
	void drawBottomBarLayout();
	void drawItemsOnBar();

	bool assignCatchedItem(item* item, bool recursion);

	void openingEquipment(const std::map<std::string, button*>& AllKeys);
	void openingChest(const std::map<std::string, button*>& AllKeys);
	void changingSelectedItem(const std::map<std::string, button*>& AllKeys);

	void puttingThrownItemToEq(ThrownItems* ThrownItem);

	std::vector<int> OrderOfSearch{ 2,0,1 };

	bool checkPossibleSpace();

	sf::Vector2i WhereToPutItem(item* Item, bool recursion);

	void updateItemsThrown(const float& dt);

	void updatePositionOfItems();

protected:

public:
	//Constructors/Destructors
	Equipment(GraphicsData* graphicsData, std::vector<std::vector<TilesOnMap*>>* Tile, EquipmentData* equipmentData, std::vector<ThrownItems*>* ItemsThrown, ThrownItems* ItemsOnTheGround);

	//Functions
	void update(const float& dt, const std::map<std::string, button*>& AllKeys);
	void render();

};

#endif // !EQUIPMENTh
