#include "Player.h"

bool Player::init()
{
	_HP = 5;
	_MP = 100;
	_AC = 5;
	return true;
}

bool Player::bindWeapon(Weapon* weapon) {
	this->m_weapon = weapon;
	if (m_weapon == nullptr)
	{
		printf("m_weapon in this player is nullptr, check wether the file used to create the weapon in right dictionary.");
		return false;
	}
	else
	{
		this->addChild(m_weapon);

		Size size = m_sprite->getContentSize();
;
		m_weapon->setPosition(Point(size.width*0.5f, size.height*0.5f));

		return true;
	}
}
