#ifndef __REMOTESOLDIERMANAGER_H__
#define __REMOTESOLDIERMANAGER_H__

#include "cocos2d.h"
#include "RemoteSoldier.h"
#include "Constant.h"
USING_NS_CC;

class RemoteSoldierManager : public Node
{
	CC_SYNTHESIZE(Scene*, _currentScene, currentScene);
	CC_SYNTHESIZE(Entity*, _player, player);
	CC_SYNTHESIZE(TMXTiledMap*, _map, map);
	CC_SYNTHESIZE(Vector<RemoteSoldier*>, m_remoteSoldierArr, SoldierArr);

public:
	static RemoteSoldierManager* create(Scene* currentScene, Entity* player, TMXTiledMap* map);
	bool init(Scene* currentScene, Entity* player, TMXTiledMap* map);
	void attackUpdate(float dt);
	void update(float dt);
	Vec2 setSoldierPosition(int num);
private:
	void createMonsters();
};

#endif
#pragma once