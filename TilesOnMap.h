#ifndef TILESONMAPH
#define TILESONMAPH

#include "StructuresOfData.h"
//Add functions for creating destroying etc.

class itemChest;

class TilesOnMap
{
private:
	GraphicsData* graphicsData;
public:
	TilesOnMap(GraphicsData* graphicsData);
	TilesOnMap(sf::Vector2i position2i, std::string NameOfTxt, GraphicsData* graphicsData);
	~TilesOnMap();

	static const int tileSize{ 44 };

	bool blokade{}; //cant walk into
	sf::Vector2i sizeOfBlockade{};
	sf::Sprite* SpritePtr{};
	int ticksToChangeItself{};
	itemChest* chest{};

	//0 - terrain like fields - to use by hoe
	//1 - crops, seeds - to pickup by hand/scythe - destroyed by pickaxe, axe, shovel, hoe
	//2 - wooden things - axable
	//3 - rocky things - pickable
	//4 - pickupable by hand like flowers, small wooden pieces, rocks
	//5 - hoed tiles - able to make croops here (no water)
	//6 - watered - able to make croops here and it will grow on here
	//7 - pure blockade
	//8 - chests - left->destroy right->open
	int typeOfTile{};

	static const int GetSizeOfTile()
	{
		return tileSize;
	}

	//Functions
	
};

#endif
