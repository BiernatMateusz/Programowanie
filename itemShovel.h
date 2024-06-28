#ifndef ITEMSHOVELH
#define ITEMSHOVELH


#include "itemTool.h"
class itemShovel :
    public itemTool
{
private:
protected:
public:
    itemShovel(GraphicsData* graphicsData);
    itemShovel(GraphicsData* graphicsData, EquipmentData* equipmentData, std::string&& name, std::vector<std::vector<TilesOnMap*>>* Tile);

    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render(sf::RenderWindow* window); //for animations
};


#endif // !ITEMSHOVELH