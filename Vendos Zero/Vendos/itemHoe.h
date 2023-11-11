#ifndef itemHoeH
#define itemHoeH

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include <iostream>
#include <vector>

#include "itemTool.h"


class itemHoe :
    public itemTool
{
private:
protected:
public:

    itemHoe(GraphicsData* graphicsData, sf::Vector2i& xyOfvec, std::string&& name);

    void update(const float& dt);
    void render(sf::RenderWindow* window); //for animations


};

#endif