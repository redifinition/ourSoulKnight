#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "cocos2d.h"

USING_NS_CC;

class Actor : public cocos2d::Sprite
{
	CC_SYNTHESIZE(int, _attack, attack);
	CC_SYNTHESIZE(Actor*, _attackTarget, attackTarget);
	CC_SYNTHESIZE(int, _attackInterval, attackInterval);
	CC_SYNTHESIZE(int, _moveSpeed, moveSpeed);
	CC_SYNTHESIZE(int, _attackRadius, attackRadius);
	CC_SYNTHESIZE(bool, _alreadyDead, alreadyDead);
	CC_SYNTHESIZE(int, _HP, HP);
	CC_SYNTHESIZE(int, _bulletSpeed, bulletSpeed);
	CC_SYNTHESIZE(Scene*, _currentScene, currentScene);
public:
	static Actor* create(const std::string& filename);
	virtual void attack(Actor* attackTarget);
	virtual void die();
	virtual void takeDamage(int damage);
	virtual bool init(const std::string& filename);


};
#endif 

