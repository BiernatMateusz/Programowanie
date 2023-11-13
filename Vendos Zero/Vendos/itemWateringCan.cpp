#include "itemWateringCan.h"

itemWateringCan::itemWateringCan(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i& xyOfvec, std::string&& name)
	:
	itemTool(graphicsData, equipmentData, xyOfvec, std::move(name))
{

}

void itemWateringCan::update(const float& dt)
{

}

void itemWateringCan::render(sf::RenderWindow* window)
{

}
