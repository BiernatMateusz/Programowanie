#include "itemSword.h"

itemSword::itemSword(GraphicsData* graphicsData)
	:
	itemTool(graphicsData)
{
}

itemSword::itemSword(GraphicsData* graphicsData, EquipmentData* equipmentData, std::string&& name, std::vector<std::vector<TilesOnMap*>>* Tile)
	:
	itemTool(graphicsData, equipmentData, std::move(name),Tile)
{

}

void itemSword::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	
}

void itemSword::render(sf::RenderWindow* window)
{

}
