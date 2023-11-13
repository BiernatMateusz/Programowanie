#include "item.h"

void item::updateKeybinds()
{

}

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

item::item(GraphicsData* graphicsData, EquipmentData* equipmentData, sf::Vector2i& xyOfvec, std::string&& name)
{
	this->Window = graphicsData->window;
	this->texturesMap = graphicsData->TexturesMap;
	this->graphicsTxtVec = graphicsData->GraphicsTxtVec;
	initGraphics(std::move(name));
	initPositon(xyOfvec, equipmentData->FirstItemPosition, equipmentData->SizeOfItems);
}

void item::update(const float& dt)
{

}

void item::render()
{
	this->Window->draw(this->itemSprite);
}



