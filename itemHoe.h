#ifndef itemHoeH
#define itemHoeH


#include "itemTool.h"


class itemHoe :
    public itemTool
{
private:
protected:
public:
    itemHoe(GraphicsData* graphicsData);
    itemHoe(GraphicsData* graphicsData, EquipmentData* equipmentData, std::string&& name, std::vector<std::vector<TilesOnMap*>>* Tile);
    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render(sf::RenderWindow* window); //for animations


};

#endif