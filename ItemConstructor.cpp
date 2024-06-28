#include "ItemConstructor.h"

void ItemConstructor::init(GraphicsData* graphicsData)
{
	this->graphicsData = graphicsData;
}

item* ItemConstructor::creatorOfItemBasedOnExample(item* example)
{
	switch (example->itemID)
	{
	case 0:
		return new item(graphicsData);
	case 20:
		return new itemHoe(graphicsData);
	case 21:
		return new itemPickaxe(graphicsData);
	case 22:
		return new itemAxe(graphicsData);
	case 23:
		return new itemSword(graphicsData);
	case 24:
		return new itemShovel(graphicsData);
	case 25:
		return new itemWateringCan(graphicsData);
	case 26:
		return new itemChest(graphicsData);
	case 100:
		return new item(graphicsData);
	case 101:
		return new item(graphicsData);

	}
}
