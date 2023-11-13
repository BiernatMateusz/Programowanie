#ifndef Structuresh
#define Structuresh

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <vector>

struct GraphicsData
{
	sf::RenderWindow* window;
	std::vector<sf::Texture*>* GraphicsTxtVec;
	std::map<std::string, sf::Texture*>* TexturesMap;
	std::map<std::string, sf::Sprite*>SpritesMap;  //deleting soon 

	std::vector<sf::Sprite*>* GraphicsSprite{};

	sf::Vector2i mousePosition;
};

struct EquipmentData
{
	sf::Vector2f FirstItemPosition{};
	int SizeOfItems = 86;
	int Y_Offset_Bar_From_Border = 150;
	int whichItemSelected{};

};

struct TilesOnMap
{
	bool blokade{}; //cant walk into
	sf::Vector2f sizeOfBlockade{};
	sf::Sprite* SpritePtr=new sf::Sprite;

	//0 - terrain like fields - to use by hoe
	//1 - crops, seeds - to pickup by hand/scythe - destroyed by pickaxe, axe, shovel, hoe
	//2 - wooden things - axable
	//3 - rocky things - pickable
	//4 - pickupable by hand like flowers, small wooden pieces, rocks
	int typeOfTile{};

};


#endif 
