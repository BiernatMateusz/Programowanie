#ifndef ITEMSWORDH
#define ITEMSWORDH

#include "itemTool.h"

class itemSword :
    public itemTool
{
private:
protected:
public:

    itemSword(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i& xyOfvec, std::string&& name);

    void update(const float& dt);
    void render(sf::RenderWindow* window); //for animations
};

#endif // !ITEMSWORDH