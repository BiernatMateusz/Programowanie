#ifndef ITEM_CONSTRUCTOR_H
#define ITEM_CONSTRUCTOR_H

#include "itemAxe.h"
#include "itemPickaxe.h"
#include "itemHoe.h"
#include "itemPickaxe.h"
#include "itemShovel.h"
#include "itemSword.h"
#include "itemChest.h"
#include "itemWateringCan.h"



class ItemConstructor
{
private:
	GraphicsData* graphicsData;
public:
	void init(GraphicsData* graphicsData);
	item* creatorOfItemBasedOnExample(item* example);



};

#endif 