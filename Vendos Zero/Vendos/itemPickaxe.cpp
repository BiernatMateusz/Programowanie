#include "itemPickaxe.h"

itemPickaxe::itemPickaxe(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i& xyOfvec, std::string&& name)
	:
	itemTool(graphicsData, equipmentData, xyOfvec, std::move(name))
{

}

void itemPickaxe::update(const float& dt)
{

}

void itemPickaxe::render(sf::RenderWindow* window)
{

}
