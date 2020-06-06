#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#include "Entity.h"
#include "Weapon.h"
USING_NS_CC;


class Player :public Entity {
	CC_SYNTHESIZE(int, _HP, HP);
	CC_SYNTHESIZE(int, _MP, MP);
	CC_SYNTHESIZE(int, _AC, AC);
public:
	Player();
	~Player();
	CREATE_FUNC(Player);
	virtual bool init();
public:
	bool bindWeapon(Weapon* Weapon);//绑定武器
private:
	Weapon* m_weapon;				//Player当前使用的武器
	Vector<Weapon*> m_weaponArr;	//Player携带的所有武器
};

#endif