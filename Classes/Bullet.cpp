#include "Bullet.h"

Bullet* Bullet::create(EActorType actorType, Entity* attackSource, Vec2 attackDirection, Scene* currentScene)
{
	Bullet* bullet = new Bullet;
	if (bullet && bullet->init(actorType, attackSource,attackDirection, currentScene))
	{
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

bool Bullet::init(EActorType actorType, Entity* attackSource, Vec2 attackDirection, Scene* currentScene)
{
	if (actorType == SHORTREMOTE)
	{
		_bulletType = "ShortRemote";
		setTexture("ShortRemoteBullet.png"); 
	}
	else if (actorType == LONGREMOTE)
	{
		_bulletType = "LongRemote";
		setTexture("LongRemoteBullet.png"); 
	}
	else
		return false;
	_attackSource = attackSource;
	_damage = attackSource->getattack();
	_attackDirection = attackDirection;
	_currentScene = currentScene;
	return true;
}

void Bullet::move()
{
	Vec2 shoutAmount = _attackDirection * _attackSource->getattackRadius();
	auto moveby = MoveBy::create(_attackSource->getattackRadius() / _attackSource->getbulletSpeed(), shoutAmount);
	auto actionRemove = RemoveSelf::create();
	this->runAction(Sequence::create(moveby, actionRemove, nullptr));
}
