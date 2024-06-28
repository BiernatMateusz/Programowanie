#include "itemChest.h"

itemChest::itemChest(GraphicsData* graphicsData)
	:
	item(graphicsData)
{
	this->items.resize(this->chestSize.x);
	for (int i = 0; i < items.size(); ++i)
		this->items[i].resize(this->chestSize.y);

	for (int i = 0; i < items.size(); ++i)
		for (int j = 0; j < items[i].size(); ++j)
			items[i][j] = nullptr;
}

itemChest::~itemChest()
{

}

item* itemChest::getItem(sf::Vector2i xyOfItems)
{
	return this->items[xyOfItems.x][xyOfItems.y];
}

void itemChest::render()
{
	for (int i = 0; i < this->items.size(); ++i)
		for (int j = 0; j < this->items[i].size(); ++j)
			if (this->getItem({ i,j }) != nullptr)
				this->items[i][j]->render();
}
