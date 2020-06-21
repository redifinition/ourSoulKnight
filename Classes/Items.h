#ifndef __ITEMS_H__
#define __ITEMS_H__

#include "cocos2d.h"
#include "Constant.h"
#include <string.h>
USING_NS_CC;
class Items : public Sprite
{
	CC_SYNTHESIZE(std::string, _itemName, itemName);
	CC_SYNTHESIZE(int, _effect, effect);
public:
	static Items* create(EItemsType ItemsType);
	bool init(EItemsType ItemsType);
};

#endif
#pragma once