#include "itemTool.h"

void itemTool::updateKeybinds()
{
	//todo -- look for block in the direction that is character looking and check possible actions
}

itemTool::itemTool(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i& xyOfvec, std::string&& name)
	:
	item(graphicsData, equipmentData, xyOfvec, std::move(name))
{

}
