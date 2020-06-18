#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#include "Entity.h"
#include "Weapon.h"
#include "Bullet.h"

USING_NS_CC;


class Player :public Entity {
//by lzy	
	CC_SYNTHESIZE(int, _MP, MP);		
	CC_SYNTHESIZE(int, _AC, AC);
	CC_SYNTHESIZE(Vec2, _weaponPosition, WpPos);				//武器固定在人物上的相对位置,默认值为player的中心
	CC_SYNTHESIZE(Weapon*, _currentWeapon, CurrentWeapon);
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	virtual bool init();

	//功能模块
	bool bindSprite(Sprite* sprite);							//绑定精灵对象
	bool bindWeapon(Weapon* Weapon);							//绑定武器
	virtual void die();											//角色死亡，删除角色并返回安全地图
	virtual void takeDamage(int damage);						//受击判定，并掉血
	void attack(Scene* currentScene, const Vec2& pos);			//攻击函数
	void rotateWeapon(const Vec2& pos);							//武器跟随攻击方向
	virtual void switchWeapon();								//接口，切换武器，角色不同切换武器的效果不同
	void pickWeapon();											//接口，拾取武器
	virtual void skill();										//技能


	void setViewPointByPlayer();
	virtual void set_tag_position(int x, int y);
	void setTiledMap(TMXTiledMap* map);
private:
	Weapon* m_weapon;											//Player当前使用的武器
	Vector<Weapon*> m_weaponArr;								//Player携带的所有武器
	TMXTiledMap* m_map;
	TMXLayer* meta;
	Point tileCoordForPosition(Point pos);
};

#endif
#pragma once