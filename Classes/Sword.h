#ifndef _Sword_H_
#define _Sword_H_

#include "Weapon.h"

class Sword: public Weapon {

public:
	Sword();										//初始化的时候添加碰撞模型
	~Sword();

	static Sword* create(const std::string& filename);
	virtual bool init(const std::string& filename);
	virtual void fire(Scene* _currentScene, const Vec2& pos, Entity* player);

private:
	Animate* attackAnimate;							//近战武器攻击动画

};

#endif // !_Sword_H_

#pragma once
