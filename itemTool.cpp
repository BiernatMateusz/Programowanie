#include "itemTool.h"

void itemTool::updateKeybinds()
{
	//todo -- look for block in the direction that is character looking and check possible actions
}

itemTool::itemTool(GraphicsData* graphicsData, EquipmentData* equipmentData,std::string&& name, std::vector<std::vector<TilesOnMap*>>* Tile)
	:
	item(graphicsData, equipmentData, std::move(name), Tile)
{

}

itemTool::itemTool(GraphicsData* graphicsData)
{
	;
}

void itemTool::update(const float& dt, const std::map<std::string, button*>& AllKeys, std::string &&nameOfTxt, std::vector<int>* TypeOfBlockToInterract, bool nullptrable)
{
	//It checks if action is possible 
	if (this->equipmentData->actionIsHappening == 0)
		item::update(dt, AllKeys);

	if (this->equipmentData->actionIsHappening == 1 and this->timePassed == 0)
	{
		//need to check if tile already exist, if so function checkFile must be started to see if tile is blocked and the if its state equals tool's state - can axe water plants?
		//always animate movement of tool in hand
		if (checkTile({ AllKeys.at("LeftMouse")->mouseTileGet().x,AllKeys.at("LeftMouse")->mouseTileGet().y }, TypeOfBlockToInterract,nullptrable))
		{
			//Need to check if its creating new tile, deleting old one or updating old one 
			//Axe - update / delete
			//Pickaxe - update / delete
			//Sword - deleting?
			//Hoe - update 
			//Shovel - update
			//Watering can - update

			initTile({ AllKeys.at("LeftMouse")->mouseTileGet().x,AllKeys.at("LeftMouse")->mouseTileGet().y }, std::move(nameOfTxt));
			this->equipmentData->needToUpdateTilesSpriteVec = 1;
			this->equipmentData->needToUpdateCameraAllSpr = 1;
		}
		else
			this->equipmentData->actionIsHappening = 0;
	}

	if (this->equipmentData->actionIsHappening == 1)
	{
		if (this->timePassed < this->timeOfItemUsage)
			this->timePassed += dt;
		else
		{
			timePassed = 0;
			this->equipmentData->actionIsHappening = 0;
		}
	}

}
