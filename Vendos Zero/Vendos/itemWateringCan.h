#ifndef WATERINGCANH
#define WATERINGCANH

#include "itemTool.h"


class itemWateringCan :
    public itemTool
{
private:
protected:
public:

    itemWateringCan(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i& xyOfvec, std::string&& name);

    void update(const float& dt);
    void render(sf::RenderWindow* window); //for animations
};

#endif // 