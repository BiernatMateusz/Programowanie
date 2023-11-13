#ifndef ITEMSHOVELH
#define ITEMSHOVELH


#include "itemTool.h"
class itemShovel :
    public itemTool
{
private:
protected:
public:

    itemShovel(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i& xyOfvec, std::string&& name);

    void update(const float& dt);
    void render(sf::RenderWindow* window); //for animations
};


#endif // !ITEMSHOVELH