#ifndef EQUIPMENTh
#define EQUIPMENTh

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "StructuresOfData.h"
#include <iostream>
#include "itemHoe.h"

//Bottom bar
//Equipment on E - new window


class Equipment
{
private:
	//Variables
	GraphicsData graphicsDataX{};
	GraphicsData *graphicsData=&graphicsDataX;

	//Bottom bar
	int WhichItemSelected = 0;
	const int NumberOfItems = 10; 
	

	sf::Sprite BottomBar;
	sf::Sprite* BottomBarPtr=&BottomBar;

	sf::Texture BottomBarTxt;
	sf::Texture* BottomBarTxtPtr=&BottomBarTxt;

	sf::Sprite BottomBarChoosen;
	sf::Sprite* BottomBarChoosenPtr = &BottomBarChoosen;

	sf::Texture BottomBarChoosenTxt;
	sf::Texture* BottomBarChoosenTxtPtr = &BottomBarChoosenTxt;

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
	void LoadNewGraphic(std::string&& name);

	void changeBar();
	void updateKeybinds();
	void initGraphics();
	void initBottomBar();
	void calculatePositionOfFirstItem();

	void initEqAndBar();
	void drawEq();
	void drawBottomBar();
protected:

public:
	//Constructors/Destructors
	Equipment(GraphicsData* graphicsData);

	//Functions
	void update();
	void render();

	
};

#endif // !EQUIPMENT
