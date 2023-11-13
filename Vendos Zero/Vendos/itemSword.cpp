#include "itemSword.h"

itemSword::itemSword(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i& xyOfvec, std::string&& name)
	:
	itemTool(graphicsData, equipmentData, xyOfvec, std::move(name))
{

}

void itemSword::update(const float& dt)
{

}

void itemSword::render(sf::RenderWindow* window)
{

}
