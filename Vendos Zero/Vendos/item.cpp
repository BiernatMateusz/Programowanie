#include "item.h"

void item::initPositon(sf::Vector2i& xyOfvec, sf::Vector2f& FirstItemPos, int& itemSize)
{
	this->itemSprite.setPosition(FirstItemPos.x + xyOfvec.x*itemSize, FirstItemPos.y+ xyOfvec.y * itemSize);
}

void item::initGraphics(std::string &&name)
{
	this->itemSprite.setTexture(*this->texturesMap->at(name));
}

item::item()
{

}

item::item(GraphicsData* graphicsData, sf::Vector2i& xyOfvec, std::string&& name)
{
	this->Window = graphicsData->window;
	this->texturesMap = graphicsData->TexturesMap;
	this->graphicsTxtVec = graphicsData->GraphicsTxtVec;
	initGraphics(std::move(name));
	initPositon(xyOfvec, graphicsData->FirstItemPosition, graphicsData->SizeOfItems);
}

sf::Sprite* item::SpritePtrToRender()
{
	sf::Sprite* tmp=&this->itemSprite;
	
	return tmp;
}

