#ifndef Structuresh
#define Structuresh

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <vector>

struct TextureData;
struct GraphicsData;
struct EquipmentData;
struct TilesOnMap;



struct GraphicsData
{
	sf::RenderWindow* window{};
	std::vector<sf::Texture*>* GraphicsTxtVec{};
	std::map<std::string, sf::Texture*>* TexturesMap{};
	std::map<std::string, TextureData*>* TextureDataMap{};

	sf::Sprite* backGround;

	std::vector<sf::Sprite*>* GraphicsSprite{};
	std::vector<sf::Sprite*>* EntitiesSprite{};
	std::vector<sf::Sprite*>* TilesSprite{};


	//mapa sprite origins -> do nazwy przypisany sf::vector2i
	//std::map<std::string, sf::Vector2i>* TexturesMap;
	//Stworzyæ mape string -> struktura grafiki, która to zawiera informacje o bloku, jego szerokosci oraz set origin 


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
	sf::Vector2i sizeOfBlockade{};
	sf::Sprite* SpritePtr;
	int ticksToChangeItself; 


	//0 - terrain like fields - to use by hoe
	//1 - crops, seeds - to pickup by hand/scythe - destroyed by pickaxe, axe, shovel, hoe
	//2 - wooden things - axable
	//3 - rocky things - pickable
	//4 - pickupable by hand like flowers, small wooden pieces, rocks
	int typeOfTile{};
};

struct TextureData
{
	sf::Vector2i origin{};
	sf::Texture *texture{};
	float offsetForPositon{};

	bool blockade{}; //cant walk into
	sf::Vector2i blockadeSize{};
};



#endif 
