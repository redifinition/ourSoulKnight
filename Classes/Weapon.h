#ifndef _Weapon_H_
#define _Weapon_H_

#include "cocos2d.h"
#include "Entity.h"
USING_NS_CC;

class Weapon :public Sprite {
	CC_SYNTHESIZE(int, _attack, Attack);						//攻击力
	CC_SYNTHESIZE(int, _mpConsumption, MpConsume);				//单次攻击能量消耗
	CC_SYNTHESIZE(int, _attackMode, Mode);						//攻击模式(远程为0，近战为1)

public:
	void hide();												//隐藏当前不使用的武器
	void show();												//切换武器时使用
	void trackTouch();											//使武器指向和鼠标指向一致
	virtual void fire(Scene* _currentScene, const Vec2& pos, Entity* player);	//开火函数
};

#endif // !__Weapon_H__

