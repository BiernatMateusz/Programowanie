#ifndef Structuresh
#define Structuresh

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <iostream>
#include <vector>
#include <set>
#include <string_view>

#include "mouseButton.h"

//#include "TilesOnMap.h"

struct TextureData;
struct GraphicsData;
struct EquipmentData;
class itemChest;

struct GraphicsData
{
	sf::RenderWindow* window{};
	std::vector<sf::Texture*>* GraphicsTxtVec{};
	std::map<std::string, sf::Texture*>* TexturesMap{};
	std::map<std::string, TextureData*>* TextureDataMap{};

	sf::Sprite* backGround{};
	sf::Sprite* player{};

	int itemID{};

	std::vector<sf::Sprite*>* GraphicsSprite{};
	std::vector<sf::Sprite*>* EntitiesSprite{};
	std::vector<sf::Sprite*>* TilesSprite{};
	std::vector<sf::Sprite*>* ItemsThrownSprite{};

	std::vector< sf::Sprite*>* AllSpritesPointer; //Update in camera

	sf::Vector2f* CenterOfMap;
	sf::Vector2i mousePosition;

	std::string directionOfPlayer{"bot"};
};

struct EquipmentData
{
	sf::Vector2f FirstItemPositionEq{};
	sf::Vector2f FirstItemPositionChest{};
	const int SizeOfItems = 86;
	const int Y_Offset_Bar_From_Border = 150;
	int whichItemSelected{};
	sf::Vector2i eqPos{};
	sf::Vector2i eqPosNew{};
	const sf::Vector2i sizeOfEq{ 10,3 };
	const int HeightOfEqPlusChest = 7; //eq->3 , chest->3 , spacing between->1
	const int OffsetHeightEqAndSpacing = HeightOfEqPlusChest - sizeOfEq.y; //7-3 = 4

	bool actionIsHappening{};
	bool needToUpdateTilesSpriteVec{};
	bool needToUpdateCameraAllSpr{};

	bool isEqOpened{};
	bool isChestOpened{};

	itemChest* openedChest{};

	bool needToUpdateEq{};
	bool needToUpdateChest{};

	sf::Vector2f scaleOfThrownItems{0.4f,0.4f};

	std::set<int>IDofItemsWhichCantBeTaken{};
};

struct TextureData
{
	sf::Vector2i origin{};
	sf::Texture *texture{};
	float offsetForPositonY{};

	bool blockade{}; //cant walk into
	sf::Vector2i blockadeSize{};
	int typeOfTile{};
	int itemID{};


	std::vector<std::vector<bool>>blocksOccupied;
	void initBlocksOccupied(std::string nameOfTxt, GraphicsData* graphicsData)
		{
			if (nameOfTxt == "Mapka")
			{
				std::vector<std::vector<bool>> twoDVector(this->texture->getSize().x/44, std::vector<bool>(this->texture->getSize().y/44, false));
				blocksOccupied = twoDVector;

				for (int i = 0; i < blocksOccupied.size(); ++i) //From top
					for (int j=0;j<5;++j)
					{
						blocksOccupied[i][j] = 1;
						blocksOccupied[i][j] = 1;
					}
				for (int i = 0; i < 3; ++i)
					for (int j = 0; j < blocksOccupied[i].size(); ++j) //From left
					{
						blocksOccupied[i][j] = 1;
						blocksOccupied[i][j] = 1;
					}
				for (int i = 0; i < blocksOccupied.size()-1; ++i) //From bot
					for (int j = blocksOccupied[i].size()-1; j > blocksOccupied[i].size()-2; --j)
					{
						blocksOccupied[i][j] = 1;
						blocksOccupied[i][j] = 1;
					}
				for (int i = blocksOccupied.size()-1; i > blocksOccupied.size()-3; --i)
					for (int j = 0; j < blocksOccupied[i].size()-1; ++j) //From right
					{
						blocksOccupied[i][j] = 1;
						blocksOccupied[i][j] = 1;
					}




			}
		}
	
};

struct MovementData
{
	bool moved{};
	std::string direction{};
};


#endif 
