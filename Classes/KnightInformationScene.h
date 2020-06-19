#ifndef _KNIGHTINFORMATION_SCENE_H
#define _KNIGHTINFORMATION_SCENE_H_


#include "cocos2d.h"
#include "startmapScene.h"
class KnightInformation : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	//void menuCloseCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	//bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void menuCloseCallback(cocos2d::Ref* pSender);
	void close_menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(KnightInformation);
private:

};
#endif
