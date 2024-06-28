#ifndef itemToolh
#define itemToolh
#include "item.h"

class itemTool :
    public item
{
private:
protected:
    int durability{};
    int breakingBlockTime{};
  
    std::vector<int>TypeOfBlockToInterract{}; //constructor needs to make vector with those numbers for every tool 

    //0 - terrain like fields - to use by hoe
    //1 - crops, seeds - to pickup by hand/scythe - destroyed by pickaxe, axe, shovel, hoe
    //2 - wooden things
    //3 - rocky things
    //4 - pickupable by hand like flowers, small wooden pieces, rocks
    //5 - hoed tiles - able to make croops here (no water)
    //6 - watered - able to make croops here and it will grow on here

    void updateKeybinds();

public:

    itemTool(GraphicsData* graphicsData, EquipmentData* equipmentData, std::string&& name, std::vector<std::vector<TilesOnMap*>>* Tile);
    itemTool(GraphicsData* graphicsData);

    virtual void update(const float& dt, const std::map<std::string, button*>& AllKeys, std::string&& nameOfTxt, std::vector<int>*TypeOfBlockToInterract, bool nullptrable);
    virtual void render(sf::RenderWindow* window)=0; //for animations

};

#endif