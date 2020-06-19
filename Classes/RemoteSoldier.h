#ifndef __REMOTESOLDIER_H__
#define __REMOTESOLDIER_H__

#include "Entity.h"
#include "Constant.h"
#include "cocos2d.h"
#include "bullet.h"
#include "Items.h"
#include <string.h>
#include <math.h>
USING_NS_CC;

class RemoteSoldier : public  Entity
{
	CC_SYNTHESIZE(std::string, _soldierType, soldierType);
public:
	static RemoteSoldier* create(EActorType soldierType,Scene* currentScene);
	bool init(EActorType soldierType, Scene* currentScene);
	void attack(Entity* attackTarget);
	bool bindSprite(Sprite* sprite);
	virtual void takeDamage(int damage);
private:
	virtual void die();
};

#endif
#pragma once