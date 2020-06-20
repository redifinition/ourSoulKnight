#include "ShotGun.h"

ShotGun::ShotGun() {
	_attack = 2;
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
	this->setScale(0.15);
	return true;
}

void ShotGun::fire(Scene* _currentScene, const Vec2& pos, Entity* player) {
	//攻击方向
	auto direction = pos - this->getParent()->getPosition();
	direction.normalize();

	direction = reduceBy15Degree(reduceBy15Degree(direction));
	//创建子弹
	for (int i = 0; i < 5; i++, direction = increaseBy15Degree(direction)) {
		auto bullet1 = Bullet::create(_bulletType, this, direction, _currentScene);
		bullet1->setScale(1.5);
		bullet1->setPosition(this->getParent()->getPosition());
		log("bullet pos:(%f, %f)", this->getParent()->getPositionX(), this->getParent()->getPositionY());
		player->getCurrentMap()->addChild(bullet1);
		bullet1->new_move();
		//break;
	}
	
}

//改变子弹方向，具体的角度改三角函数里的值计可
Vec2 ShotGun::increaseBy15Degree(const Vec2& pos) {
	Vec2 new_pos(0, 0);
	new_pos.x = cos(PI / 12)*pos.x - sin(PI / 12)*pos.y;
	new_pos.y = sin(PI / 12)*pos.x + cos(PI / 12)*pos.y;
	return new_pos;

}
Vec2 ShotGun::reduceBy15Degree(const Vec2& pos) {
	Vec2 new_pos(0, 0);
	new_pos.x = cos(PI / 12)*pos.x + sin(PI / 12)*pos.y;
	new_pos.y = -sin(PI / 12)*pos.x + cos(PI / 12)*pos.y;
	return new_pos;
}
