#ifndef __SAFETYMAP_SCENE_H__
#define __SAFETYMAP_SCENE_H__

#include "cocos2d.h"
#include  "allHeadFiles.h"
using namespace cocos2d;

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
	TMXTiledMap *_tiledmap;								//地图类中相关地图
	TMXLayer *_background;								//背景层
	Sprite *_player;

	Player* m_player;
	Player* m_monster;									//先用player类替代

};

#endif // __SAFETYMAP_SCENE_H__

