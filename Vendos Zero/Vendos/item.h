#ifndef item_h
#define item_h

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "StructuresOfData.h"
#include <iostream>
#include <array>
#include <vector>

class item
{
private:
	
protected:
	sf::RenderWindow* Window;
	
	
	std::vector<sf::Texture*>*graphicsTxtVec;
	std::map<std::string, sf::Texture*>*texturesMap;

	virtual void updateKeybinds();
	void initPositon(sf::Vector2i& xyOfvec, sf::Vector2f& FirstItemPos, int& itemSize);
	void initGraphics(std::string&& name);
public:
	//Constructos
	item();
	item(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i& xyOfvec, std::string&& name);


	//Functions
	virtual void update(const float &dt);
	virtual void render(); //for animations

	//Variables
	sf::Sprite itemSprite;
};

#endif 