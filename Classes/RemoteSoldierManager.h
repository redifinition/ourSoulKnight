#ifndef __REMOTESOLDIERMANAGER_H__
#define __REMOTESOLDIERMANAGER_H__

#include "cocos2d.h"
#include "RemoteSoldier.h"
#include "Constant.h"
USING_NS_CC;

class RemoteSoldierManager : public Node
{
	CC_SYNTHESIZE(Scene*, _currentScene, currentScene);
public:
	static RemoteSoldierManager* create(Scene* currentScene);
	bool init(Scene* currentScene);

	void update(float dt);
private:
	void createMonsters();
	Vector<RemoteSoldier*> m_remoteSoldierArr;
};
#endif
