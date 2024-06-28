#include "itemAxe.h"

itemAxe::itemAxe(GraphicsData* graphicsData)
	:
	itemTool(graphicsData)
{

}

itemAxe::itemAxe(GraphicsData* graphicsData, EquipmentData* equipmentData,  std::string&& name, std::vector<std::vector<TilesOnMap*>>* Tile)
	:
	itemTool(graphicsData, equipmentData, std::move(name), Tile)
{

}

void itemAxe::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{

}

void itemAxe::render(sf::RenderWindow* window)
{

}
