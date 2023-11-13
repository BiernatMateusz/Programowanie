#ifndef EQUIPMENTh
#define EQUIPMENTh

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "StructuresOfData.h"
#include <iostream>
#include "itemHoe.h"
#include "itemPickaxe.h"
#include "itemAxe.h"
#include "itemSword.h"
#include "itemShovel.h"
//Bottom bar
//Equipment on E - new window


class Equipment
{
private:
	//Variables
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;

	//Bottom bar
	const int NumberOfItems = 10; 
	
	sf::Sprite* BottomBarPtr;

	sf::Texture* BottomBarTxtPtr;

	sf::Sprite* BottomBarChoosenPtr;

	sf::Texture* BottomBarChoosenTxtPtr;

	std::vector<sf::Sprite*>BottomBarSprites;

	//Vectors of items
	const sf::Vector2i sizeOfEq{ 10,3 };

	//All eq
	std::vector<std::vector<item*>>Eq{};
	std::vector<item*>BotBarPtr;
	

	//Other
	sf::Vector2f MapBorder{};
	

	//Items
	
	
	

	//Additional functions
	void changeBar();
	void updateKeybinds();
	void initGraphics();
	void initBottomBar();
	void calculatePositionOfFirstItem();

	void initEqAndBar();
	void drawEq();
	void drawBottomBar();
	void updateBottomBar();
protected:

public:
	//Constructors/Destructors
	Equipment(GraphicsData* graphicsData);

	//Functions
	void update();
	void render();

	
};

#endif // !EQUIPMENT
