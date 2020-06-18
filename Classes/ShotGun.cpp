#include "ShotGun.h"

ShotGun::ShotGun() {
	_attack = 3;
	_attackMode = 1;
	_mpConsumption = 2;
	_bulletSpeed = 1000;
	_bulletType = SHORTREMOTE;

	//武器位置
	this->setAnchorPoint(Vec2(0.1, 0.1));
}
ShotGun::~ShotGun() {

}

ShotGun* ShotGun::create(const std::string& filename)
{
	ShotGun* sprite = new ShotGun;
	if (sprite && sprite->init(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool ShotGun::init(const std::string& filename)
{
	if (!Sprite::initWithFile(filename)) {
		return false;
	}
	return true;
}

void ShotGun::fire(Scene* _currentScene, const Vec2& pos) {
	//攻击方向
	auto direction = pos - this->getParent()->getPosition();
	direction.normalize();

	direction = reduceBy30Degree(reduceBy30Degree(direction));
	//创建子弹
	for (int i = 0; i < 5; i++, direction = increaseBy30Degree(direction)) {
		auto bullet1 = Bullet::create(_bulletType, this, direction, _currentScene);
		bullet1->setScale(1.5);
		bullet1->setPosition(this->getParent()->getPosition());
		_currentScene->addChild(bullet1);
		bullet1->new_move();
	}
	
}

Vec2 ShotGun::increaseBy30Degree(const Vec2& pos) {
	Vec2 new_pos(0, 0);
	new_pos.x = 0.5*(sqrt(3)*pos.x - pos.y);
	new_pos.y = 0.5*(pos.x - sqrt(3)*pos.y);
	return new_pos;

}
Vec2 ShotGun::reduceBy30Degree(const Vec2& pos) {
	Vec2 new_pos(0, 0);
	new_pos.x = 0.5*(sqrt(3)*pos.x + pos.y);
	new_pos.y = 0.5*(pos.x + sqrt(3)*pos.y);
	return new_pos;
}
