#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#include "Entity.h"
#include "Weapon.h"
#include "Bullet.h"

USING_NS_CC;


class Player :public Entity {
//by lzy
	CC_SYNTHESIZE(int, _HP, HP);		
	CC_SYNTHESIZE(int, _MP, MP);		
	CC_SYNTHESIZE(int, _AC, AC);
	CC_SYNTHESIZE(Vec2, _weaponPosition, WpPos);				//武器固定在人物上的相对位置,默认值为player的中心
	CC_SYNTHESIZE(Weapon*, _currentWeapon, CurrentWeapon);
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	virtual bool init();
//by lzy
	bool bindSprite(Sprite* sprite);							//同时添加物理碰撞模型
	bool bindWeapon(Weapon* Weapon);							//绑定武器

	void attack(Scene* currentScene, const Vec2& pos);			//调用攻击函数,还需要添加连发的功能
	virtual void switchWeapon();								//接口，切换武器，角色不同切换武器的效果不同
	void pickWeapon();											//接口，拾取武器
	virtual void skill();										//技能
//by lq
	void setViewPointByPlayer();
	virtual void set_tag_position(int x, int y);
	void setTiledMap(TMXTiledMap* map);
private:
//by lzy
	Weapon* m_weapon;											//Player当前使用的武器
	Vector<Weapon*> m_weaponArr;								//Player携带的所有武器
//by lq
	TMXTiledMap* m_map;
	TMXLayer* meta;
	Point tileCoordForPosition(Point pos);
};

#endif