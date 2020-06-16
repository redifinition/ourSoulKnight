#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "cocos2d.h"
#include "Controller.h"
#include "ControllerListener.h"
using namespace cocos2d;

class Entity :public Node,public ControllerListener
{
	//by lkd
	CC_SYNTHESIZE(int, _attack, attack);
	CC_SYNTHESIZE(Entity*, _attackTarget, attackTarget);
	CC_SYNTHESIZE(int, _attackInterval, attackInterval);
	CC_SYNTHESIZE(int, _moveSpeed, moveSpeed);
	CC_SYNTHESIZE(int, _attackRadius, attackRadius);
	CC_SYNTHESIZE(bool, _alreadyDead, alreadyDead);
	CC_SYNTHESIZE(int, _HP, HP);
	CC_SYNTHESIZE(int, _bulletSpeed, bulletSpeed);
	CC_SYNTHESIZE(Scene*, _currentScene, currentScene);
//by lzy
	CC_SYNTHESIZE(Sprite*, m_sprite, Sprite);
public:
//by lzy
	Entity();
	~Entity();
//by lzy
	bool bindSprite(Sprite* sprite);	
//by lq
	void set_controller(My_Controller* controller);
	virtual void set_tag_position(int x, int y);
	virtual Point get_tag_position();
protected:
//by lq
	My_Controller* m_controller;

};
#endif
