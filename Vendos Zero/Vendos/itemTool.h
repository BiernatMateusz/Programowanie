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
    int TypeOfBlockToInterract{}; 
    //0 - terrain like fields - to use by hoe
    //1 - crops, seeds - to pickup by hand/scythe - destroyed by pickaxe, axe, shovel, hoe
    //2 - wooden things
    //3 - rocky things
    //4 - pickupable by hand like flowers, small wooden pieces, rocks

    void updateKeybinds();

public:

    itemTool(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i& xyOfvec, std::string&& name);

    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderWindow* window) = 0; //for animations

};

#endif