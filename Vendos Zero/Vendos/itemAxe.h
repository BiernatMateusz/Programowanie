#ifndef ITEMAXEH
#define ITEMAXEH

#include "itemTool.h"
class itemAxe :
    public itemTool
{
private:
protected:
public:

    itemAxe(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i& xyOfvec, std::string&& name);

    void update(const float& dt);
    void render(sf::RenderWindow* window); //for animations
};

#endif 