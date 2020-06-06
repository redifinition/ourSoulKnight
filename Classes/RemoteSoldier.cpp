#include "RemoteSoldier.h"

RemoteSoldier* RemoteSoldier::create(EActorType soldierType,Scene* currentScene)
{
	RemoteSoldier* sprite = new RemoteSoldier;
	if (sprite && sprite->init(soldierType, currentScene))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
bool RemoteSoldier::init(EActorType soldierType, Scene* currentScene)
{
	if (soldierType == SHORTREMOTE)
	{
		setTexture("ShortRemoteSoldier.png");  //缺少素材
		_soldierType = "ShortRemote";
		_attack = SHORT_REMOTE_SOLDIER_ATTACK;
		_attackRadius = SHORT_REMOTE_SOLDIER_ATTACK_RADIUS;
	}
	else if (soldierType == LONGREMOTE)
	{
		setTexture("LongRemoteSoldier.png");  //缺少素材
		_soldierType = "LongRemote";
		_attack = LONG_REMOTE_SOLDIER_ATTACK;
		_attackRadius = LONG_REMOTE_SOLDIER_ATTACK_RADIUS;
	}
	else
		return false;
	_attackInterval = SOLDIER_ATTACK_INTERVAL;
	_alreadyDead = false;
	_HP = REMOTE_SOLDIER_HP;
	_moveSpeed = REMOTE_SOLDIER_MOVE_SPEED;
	_attackTarget = nullptr;
	_currentScene = currentScene;
	_bulletSpeed = SOLDIER_BULLET_SPEED;
	auto physicsBody = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(0x01);    // 0001
	physicsBody->setContactTestBitmask(0x02); // 0010
	this->setPhysicsBody(physicsBody);
	this->setTag(REMOTE_SOLDIER_TAG);
	return true;
}

void RemoteSoldier::move()
{
	//todo:有关边界的处理
	auto action1 = MoveBy::create(50 / _moveSpeed, Vec2(50, 0));
	auto action2 = MoveBy::create(50 / _moveSpeed, Vec2(-50, 0));
	auto sequence = Sequence::create(action1, action2, nullptr);
	this->runAction(RepeatForever::create(sequence));
}

void RemoteSoldier::attack(Actor* attackTarget)
{
	_attackTarget = attackTarget;
	Vec2 attackPosition = _attackTarget->getPosition();
	Vec2 Distance = attackPosition - this->getPosition();
	Vec2 direction = Distance.getNormalized();
	if (_soldierType == "ShortRemote") 
	{
		auto bullet1 = Bullet::create(SHORTREMOTE, this, direction, _currentScene);
		direction.rotate(Vec2(0, 0), 0.5);
		auto bullet2 = Bullet::create(SHORTREMOTE, this, direction, _currentScene);
		direction.rotate(Vec2(0, 0), -1.0);
		auto bullet3 = Bullet::create(SHORTREMOTE, this, direction, _currentScene);
		bullet1->setPosition(this->getPosition());
		bullet2->setPosition(this->getPosition());
		bullet3->setPosition(this->getPosition());
		_currentScene->addChild(bullet1);
		_currentScene->addChild(bullet2);
		_currentScene->addChild(bullet3);
		bullet1->move();
		bullet2->move();
		bullet3->move();
	}
	else if (_soldierType == "LongRemote")
	{
		auto bullet = Bullet::create(LONGREMOTE, this, direction, _currentScene);
		bullet->setPosition(this->getPosition());
		_currentScene->addChild(bullet);
		bullet->move();
	}
}
void RemoteSoldier::takeDamage(int damage)
{
	_HP -= damage;
	if (_HP <= 0)
	{
		_alreadyDead = true;
		this->die();
	}
}

void RemoteSoldier::die()
{
	_currentScene->removeChild(this);
	//todo:在道具类完成后补充
}