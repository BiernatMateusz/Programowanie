#include "itemShovel.h"

itemShovel::itemShovel(GraphicsData* graphicsData)
	:
	itemTool(graphicsData)
{
}

itemShovel::itemShovel(GraphicsData* graphicsData, EquipmentData* equipmentData, std::string&& name, std::vector<std::vector<TilesOnMap*>>* Tile)
	:
	itemTool(graphicsData, equipmentData, std::move(name), Tile)
{

}

void itemShovel::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	
}

void itemShovel::render(sf::RenderWindow* window)
{

}
