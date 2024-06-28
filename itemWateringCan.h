#ifndef WATERINGCANH
#define WATERINGCANH

#include "itemTool.h"


class itemWateringCan :
    public itemTool
{
private:
protected:
public:
    itemWateringCan(GraphicsData* graphicsData);
    itemWateringCan(GraphicsData* graphicsData, EquipmentData* equipmentData, std::string&& name, std::vector<std::vector<TilesOnMap*>>* Tile);

    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render(sf::RenderWindow* window); //for animations
};

#endif // 