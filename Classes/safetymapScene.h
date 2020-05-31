#ifndef __SAFETYMAP_SCENE_H__
#define __SAFETYMAP_SCENE_H__

#include "cocos2d.h"

class safetymap: public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	//void add_player(TMXTiledMap* map);

	CREATE_FUNC(safetymap);
private:
	cocos2d::TMXTiledMap *_tiledmap;//��ͼ������ص�ͼ
	cocos2d::TMXLayer *_background;//������
	cocos2d::Sprite *_player;
};

#endif // __SAFETYMAP_SCENE_H__

