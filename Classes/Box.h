#ifndef  __BOX_H__
#define __BOX_H__

#include "cocos2d.h"
#include "Items.h"
USING_NS_CC;

class Box : public Sprite
{
    CC_SYNTHESIZE(int, _goodsType, goodsType);
    CC_SYNTHESIZE(Scene*, _currentScene, currentScene)
public:
    static Box* create(Scene* currentScene);
    bool init(Scene* currentScene);
    void open();
};

#endif
#pragma once