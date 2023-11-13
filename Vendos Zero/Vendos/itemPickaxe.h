#ifndef itemPickaxeH
#define itemPickaxeH

#include "itemTool.h"


class itemPickaxe :
    public itemTool
{
private:
protected:
public:

    itemPickaxe(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i& xyOfvec, std::string&& name);

    void update(const float& dt);
    void render(sf::RenderWindow* window); //for animations
};

#endif // !itemPickaxeH