#ifndef _ShotGun_H_
#define _ShotGun_H_

#include "Gun.h"
class ShotGun :public Gun {
public:
	ShotGun();													//用于初始化武器的属性，之后放到各个武器的类里面去
	~ShotGun();													//析构函数好像没啥用，先放在这
	static ShotGun* create(const std::string& filename);
	virtual bool init(const std::string& filename);
	
	Vec2 increaseBy30Degree(const Vec2& pos);
	Vec2 reduceBy30Degree(const Vec2& pos);
	virtual void fire(Scene* currentScene, const Vec2& pos);
	
};

#endif
#pragma once