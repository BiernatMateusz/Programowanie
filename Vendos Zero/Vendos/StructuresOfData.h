#ifndef Structuresh
#define Structuresh

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <vector>

struct GraphicsData
{
	sf::RenderWindow* window;
	sf::Vector2f FirstItemPosition{};
	int SizeOfItems = 86;
	std::vector<sf::Texture*>* GraphicsTxtVec;
	std::map<std::string, sf::Texture*>* TexturesMap;
	std::map<std::string, sf::Sprite*>SpritesMap;  //deleting soon 
	int Y_Offset_Bar_From_Border = 150;

	sf::Vector2i mousePosition;
};

#endif 
