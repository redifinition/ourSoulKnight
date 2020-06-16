#ifndef __REMOTESOLDIER_H__
#define __REMOTESOLDIER_H__

#include "Actor.h"
#include "Constant.h"
#include "cocos2d.h"
#include "bullet.h"
#include <string.h>
#include <math.h>
USING_NS_CC;

class RemoteSoldier : public  Actor
{
	CC_SYNTHESIZE(std::string, _soldierType, soldierType);
public:
	static RemoteSoldier* create(EActorType soldierType,Scene* currentScene);
	void move();
	void attack(Actor* attackTarget);
	void takeDamage(int damage);
	bool init(EActorType soldierType, Scene* currentScene);
private:
	 void die();
};
#endif