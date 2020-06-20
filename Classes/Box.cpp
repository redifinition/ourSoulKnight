#include "Box.h"

Box* Box::create(Scene* currentScene)
{
	Box* box = new(Box);
	if (box && box->init(currentScene))
	{
		box->autorelease();
			return box;
	}
	CC_SAFE_DELETE(box);
		return nullptr;
}

bool Box::init(Scene* currentScene)
{
	setTexture("LockedBox.png");
	srand((unsigned)time(nullptr));
	_currentScene = currentScene;
	_goodsType = rand() % 6;
	return true;
}

void Box::open()
{
	setTexture("OpenedBox.png");
	if(_goodsType == RED_BOTTLE)
	{
		Items* item = Items::create(REDBOTTLE);
		item->setPosition(this->getPosition());
		_currentScene->addChild(item);
	}
	else if(_goodsType == BLUE_BOTTLE)
	{
		Items* item = Items::create(BLUEBOTTLE);
		item->setPosition(this->getPosition());
		_currentScene->addChild(item);
	}
	else if(_goodsType)
	{
		//todo:µÈ´ıÎäÆ÷ÀàÍêÉÆ
	}
}