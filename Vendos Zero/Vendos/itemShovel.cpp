#include "itemShovel.h"

itemShovel::itemShovel(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i& xyOfvec, std::string&& name)
	:
	itemTool(graphicsData, equipmentData, xyOfvec, std::move(name))
{

}

void itemShovel::update(const float& dt)
{

}

void itemShovel::render(sf::RenderWindow* window)
{

}
