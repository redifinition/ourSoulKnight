#include "Gun.h"
#include <math.h>

Gun::Gun() {
	_attack = 2;
	_attackMode = 1;
	_mpConsumption = 0;
	_bulletSpeed = 1000;
	_bulletType = LONGREMOTE;
	this->setAnchorPoint(Vec2(0.1, 0.1));
}
Gun::~Gun() {

}

Gun* Gun::create(const std::string& filename)
{
	Gun* sprite = new Gun;
	if (sprite && sprite->init(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Gun::init(const std::string& filename)
{
	if (!Sprite::initWithFile(filename)) {
		return false;
	}
	this->setScale(0.08);
	return true;
}

void Gun::fire(Scene* _currentScene, const Vec2& pos, Entity* player) {

	//攻击方向
	auto direction = pos - this->getParent()->getPosition();
	direction.normalize();

	//创建子弹
	auto bullet = Bullet::create(_bulletType, this, direction, _currentScene);
	bullet->setScale(1.5);
	bullet->setPosition(this->getParent()->getPosition());
	player->getCurrentMap()->addChild(bullet);
	bullet->new_move();
}