#include "Items.h"

Items* Items::create(EItemsType ItemsType)
{
	Items* item = new Items;
	if (item && item->init(ItemsType))
	{
		item->autorelease();
		return item;
	}
	CC_SAFE_DELETE(item);
	return nullptr;
}

bool Items::init(EItemsType ItemsType)
{
	if (ItemsType == REDBOTTLE)
	{
		setTexture("RedBottle.png");
		_itemName = "redBottle";
		_effect = 2;
		return true;
	}
	else if (ItemsType == BLUEBOTTLE)
	{
		setTexture("BlueBottle.png");
		_itemName = "blueBottle";
		_effect = 80;
		return true;
	}
	else
		return false;
}