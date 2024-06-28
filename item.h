#ifndef item_h
#define item_h

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <iostream>
#include <array>
#include <vector>
#include <String>
#include "TilesOnMap.h"

class item
{
private:
	sf::Font font{};
	sf::Text numberOfItems{};
	int maxStack{ 999 };
	bool OverMax{};

	void updateAndRenderNumberOfItems();

protected:
	sf::RenderWindow* Window;
	
	GraphicsData* graphicsData;
	EquipmentData* equipmentData;

	std::vector<std::vector<TilesOnMap*>>* Tile;

	float timeOfItemUsage{1}; //create map of times then every item needs it 
	float timePassed{};

	std::string nameOfTxt;

	int numberOfItemsInStack{ 1 };


	void updateKeybinds(const float& dt, const std::map<std::string, button*>& AllKeys);
	
	void initGraphics(std::string&& name);
	bool checkTile(sf::Vector2i&& position2i, std::vector<int>* TypeOfBlockToInterract, bool nullptrable);
	void initTile(sf::Vector2i&& position2i, std::string&& NameOfTxt);
	
public:

	//Constructos
	item() {};
	item(GraphicsData* graphicsData);
	item(GraphicsData* graphicsData, EquipmentData* equipmentData, std::string&& name, std::vector<std::vector<TilesOnMap*>>*Tile);

	//Assign operators
	virtual item& operator=(const item& model);

	//Functions
	virtual void update(const float &dt, const std::map<std::string, button*>& AllKeys); //actions
	virtual void render(); //for animations

	void initPositon(sf::Vector2i xyOfvec, sf::Vector2f FirstItemPos, const int& itemSize, int OffsetYPositioning);

	bool checkClickedTile(sf::Vector2i&& position2i);

	void changeNumberOfItems(int newNumberOfItems);
	int getNumberOfItems();
	int getNumberMax();

	bool addItemsReturn1IfOverMax(item* itemPtr);
	void substrFromThisItem(int value);
	void addToThisItem(int value);

	bool checkIfAddable();

	//Variables
	int itemID{};
	sf::Sprite itemSprite{};
	sf::Vector2i TileClicked{};

};

#endif 