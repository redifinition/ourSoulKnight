#ifndef _KnightSTARTMAP_SCENE_H_
#define _KnightSTARTMAP_SCENE_H_

#include "cocos2d.h"
using namespace cocos2d;

class  KnightStartMap : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void startgame();
	CREATE_FUNC(KnightStartMap);
private:
	cocos2d::TMXTiledMap *_tiledmap;//地图类中相关地图
	cocos2d::TMXLayer *_background;//背景层
	cocos2d::Sprite *_player;


};


#endif //KnightstartmapScene.h !


