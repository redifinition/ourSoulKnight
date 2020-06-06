#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Actor.h"
#include "RemoteSoldier.h"
#include "Constant.h"
#include <string.h>
USING_NS_CC;

class Bullet : public cocos2d::Sprite
{
	CC_SYNTHESIZE(Actor *, _attackSource, attackSource);
	CC_SYNTHESIZE(Vec2, _attackDirection,attackDirection);
	CC_SYNTHESIZE(int, _damage, damage);
	CC_SYNTHESIZE(std::string, _bulletType, bulletType);
	CC_SYNTHESIZE(Scene*, _currentScene, currentScene);
public:
	static Bullet* create(EActorType actorType,Actor* attackSource, Vec2 attackDirection, Scene* currentScene);
	bool init(EActorType actorType, Actor* attackSource, Vec2 attackDirection, Scene* currentScene);
	void move();
};
#endif 

