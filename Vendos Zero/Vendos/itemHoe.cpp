#include "itemHoe.h"

itemHoe::itemHoe(GraphicsData* graphicsData, sf::Vector2i& xyOfvec, std::string&& name)
	:
	itemTool(graphicsData, xyOfvec, std::move(name))
{
	update(3);
}

void itemHoe::update(const float& dt)
{
	//std::cout << &itemSprite << "\n";
	//std::cout << SpritePtrToRender() << "\n"; //its the same
}

void itemHoe::render(sf::RenderWindow* window)
{

}
