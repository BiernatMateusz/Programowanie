#include "itemWateringCan.h"

itemWateringCan::itemWateringCan(GraphicsData* graphicsData)
	:
	itemTool(graphicsData)
{
}

itemWateringCan::itemWateringCan(GraphicsData* graphicsData, EquipmentData* equipmentData, std::string&& name, std::vector<std::vector<TilesOnMap*>>* Tile)
	:
	itemTool(graphicsData, equipmentData, std::move(name), Tile)
{
	TypeOfBlockToInterract.push_back(5);
}

void itemWateringCan::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	itemTool::update(dt, AllKeys, "PoDziabceMokre", &this->TypeOfBlockToInterract,0);
}

void itemWateringCan::render(sf::RenderWindow* window)
{

}
