#ifndef _ShotGun_H_
#define _ShotGun_H_

#include "Gun.h"
class ShotGun :public Gun {
public:
	ShotGun();													//用于初始化武器的属性，之后放到各个武器的类里面去
	~ShotGun();													//析构函数好像没啥用，先放在这
	static ShotGun* create(const std::string& filename);
	virtual bool init(const std::string& filename);
	
	Vec2 increaseBy15Degree(const Vec2& pos);					//改变子弹的发射角度 +30°
	Vec2 reduceBy15Degree(const Vec2& pos);						//改变子弹的发射角度 -30°
	virtual void fire(Scene* _currentScene, const Vec2& pos, Entity* player);
	
};

#endif
#pragma once