#ifndef ITEMAXEH
#define ITEMAXEH

#include "itemTool.h"
class itemAxe :
    public itemTool
{
private:
protected:
public:
    itemAxe(GraphicsData* graphicsData);
    itemAxe(GraphicsData* graphicsData, EquipmentData* equipmentData, std::string&& name, std::vector<std::vector<TilesOnMap*>>*Tile);

    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render(sf::RenderWindow* window); //for animations
};

#endif 