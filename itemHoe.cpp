#include "itemHoe.h"

itemHoe::itemHoe(GraphicsData* graphicsData)
	:
	itemTool(graphicsData)
{

}

itemHoe::itemHoe(GraphicsData* graphicsData, EquipmentData* equipmentData, std::string&& name, std::vector<std::vector<TilesOnMap*>>* Tile)
	:
	itemTool(graphicsData, equipmentData, std::move(name),Tile)
{
	TypeOfBlockToInterract.push_back(0);
	TypeOfBlockToInterract.push_back(1);
}

void itemHoe::update(const float& dt, const std::map<std::string, button*>& AllKeys)
{
	itemTool::update(dt, AllKeys,"PoDziabceSuche", &this->TypeOfBlockToInterract,1);
	
}

void itemHoe::render(sf::RenderWindow* window)
{
	//action
}
