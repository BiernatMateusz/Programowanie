#include "itemAxe.h"

itemAxe::itemAxe(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i& xyOfvec, std::string&& name)
	:
	itemTool(graphicsData, equipmentData, xyOfvec, std::move(name))
{

}

void itemAxe::update(const float& dt)
{

}

void itemAxe::render(sf::RenderWindow* window)
{

}
