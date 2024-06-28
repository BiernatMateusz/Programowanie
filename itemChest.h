#ifndef ITEMCHEST_H
#define ITEMCHEST_H

//CHEST SIZE 10x4

#include "item.h"

class itemChest :
    public item
{
private:
   // std::vector<std::vector<item*>> items;
public:
    itemChest(GraphicsData* graphicsData);
    ~itemChest();

    const sf::Vector2i chestSize{10,3};
    std::vector<std::vector<item*>> items;

    item* getItem(sf::Vector2i xyOfItems);
    void render();
};

#endif // !ITEMCHEST_H