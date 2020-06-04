#include "Actor.h"

Actor* Actor::create(const std::string& filename)
{
	Actor* sprite = new Actor;
	if (sprite && sprite->init(filename))
	{
		sprite->autorelease();
	return sprite;
}
CC_SAFE_DELETE(sprite);
return nullptr;
}

bool Actor::init(const std::string& filename)
{
	if (!Sprite::initWithFile(filename)) {
		return false;
	}
	return true;
}

void Actor::die()
{
}

void Actor::attack(Actor* attackTarget)
{

}

void Actor::takeDamage(int damage)
{
	_HP -= damage;
	if (_HP <= 0)
	{
		_alreadyDead = true;
		this->die();
	}
}