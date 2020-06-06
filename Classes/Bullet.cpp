#include "Bullet.h"

Bullet* Bullet::create(EActorType actorType, Actor* attackSource, Vec2 attackDirection, Scene* currentScene)
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

bool Bullet::init(EActorType actorType, Actor* attackSource, Vec2 attackDirection, Scene* currentScene)
{
	if (actorType == SHORTREMOTE)
	{
		_bulletType = "ShortRemote";
		setTexture("ShortRemoteBullet.png"); //缺少素材
		auto physicsBody = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
		physicsBody->setDynamic(false);
		physicsBody->setCategoryBitmask(0x01);    // 0001
		physicsBody->setContactTestBitmask(0x02); // 0010
		this->setPhysicsBody(physicsBody);
		this->setTag(SHORT_REMOTE_SOLDIER_TAG);
	}
	else if (actorType == LONGREMOTE)
	{
		_bulletType = "LongRemote";
		setTexture("LongRemoteBullet.png"); //缺少素材
		auto physicsBody = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
		physicsBody->setDynamic(false);
		physicsBody->setCategoryBitmask(0x01);    // 0001
		physicsBody->setContactTestBitmask(0x02); // 0010
		this->setPhysicsBody(physicsBody);
		this->setTag(LONG_REMOTE_SOLDIER_TAG);
	}
	else if (actorType == PLAYER)
	{
		//todo:角色类完成后补充
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
	this->runAction(moveby);
}
