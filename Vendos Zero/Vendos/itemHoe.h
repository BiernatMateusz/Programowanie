#ifndef itemHoeH
#define itemHoeH


#include "itemTool.h"


class itemHoe :
    public itemTool
{
private:
protected:
public:

    itemHoe(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i& xyOfvec, std::string&& name);

    void update(const float& dt);
    void render(sf::RenderWindow* window); //for animations


};

#endif