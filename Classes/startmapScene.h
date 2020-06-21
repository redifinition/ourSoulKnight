#ifndef _STARTMAP_SCENE_H_
#define _STARTMAP_SCENE_H_

#include "cocos2d.h"
using namespace cocos2d;

class  startmap: public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuCloseCallbackHome(cocos2d::Ref* pSender);
	CREATE_FUNC(startmap);
private:
	TMXTiledMap* _safetymap;
	int audio_begin_flag=0;

};


#endif //startmapScene.h !

