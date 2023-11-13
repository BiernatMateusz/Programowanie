#include "itemHoe.h"

itemHoe::itemHoe(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i& xyOfvec, std::string&& name)
	:
	itemTool(graphicsData, equipmentData, xyOfvec, std::move(name))
{
	
}

void itemHoe::update(const float& dt)
{

}

void itemHoe::render(sf::RenderWindow* window)
{

}
