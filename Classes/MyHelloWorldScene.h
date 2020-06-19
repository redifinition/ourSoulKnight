#ifndef __MYHELLOWORLD_SCENE_H__
#define __MYHELLOWORLD_SCENE_H__

#include "cocos2d.h"

class MyHelloWorld : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void newgame_menuCloseCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(MyHelloWorld);
};

#endif // __MYHELLOWORLD_SCENE_H__
#pragma once