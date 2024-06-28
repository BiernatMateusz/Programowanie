#ifndef itemPickaxeH
#define itemPickaxeH

#include "itemTool.h"


class itemPickaxe :
    public itemTool
{
private:
protected:
public:
    itemPickaxe(GraphicsData* graphicsData);
    itemPickaxe(GraphicsData* graphicsData, EquipmentData* equipmentData, std::string&& name, std::vector<std::vector<TilesOnMap*>>* Tile);

    void update(const float& dt, const std::map<std::string, button*>& AllKeys);
    void render(sf::RenderWindow* window); //for animations
};

#endif // !itemPickaxeH