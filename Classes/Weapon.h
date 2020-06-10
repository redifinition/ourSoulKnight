#ifndef __Weapon_H__
#define __Weapon_H__

#include "cocos2d.h"
USING_NS_CC;

class Weapon :public Sprite {
	CC_SYNTHESIZE(int, _attack, Attack);						//攻击力
	CC_SYNTHESIZE(int, _mpConsumption, MpConsume);				//单次攻击能量消耗
	CC_SYNTHESIZE(int, _attackMode, Mode);						//攻击模式(远程为0，近战为1)
	CC_SYNTHESIZE(int, _bulletType, BulletType);				//武器使用的子弹类型，近战则没有

public:
//by lzy
	//static Weapon* create(const std::string& filename);
	//virtual bool init(const std::string& filename);
	virtual void fire(Scene* currentScene,const Vec2& pos) ;
	void hide();												//隐藏当前不使用的武器
	void show();												//切换武器时使用
	void trackTouch();											//使武器指向和鼠标指向一致
};
#endif // !__Weapon_H__
