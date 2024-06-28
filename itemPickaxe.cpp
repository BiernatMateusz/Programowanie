#include "itemPickaxe.h"

itemPickaxe::itemPickaxe(GraphicsData* graphicsData)
	:
	itemTool(graphicsData)
{
}

itemPickaxe::itemPickaxe(GraphicsData* graphicsData, EquipmentData* equipmentData, std::string&& name, std::vector<std::vector<TilesOnMap*>>* Tile)
	:
	itemTool(graphicsData, equipmentData, std::move(name), Tile)
{
	TypeOfBlockToInterract.push_back(3);
}

void itemPickaxe::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{

}

void itemPickaxe::render(sf::RenderWindow* window)
{

}
