#ifndef __SETUP_SCENE_H__
#define __SETUP_SCENE_H__

#include "cocos2d.h"

class setup : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void audio_menuCloseCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	void volume_menuCloseCallback(Ref* pSender);
	void newgame_menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(setup);
};

#endif // __SETUP_SCENE_H__
#pragma once