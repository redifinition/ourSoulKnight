#include "Gun.h"
#include <math.h>

Gun::Gun() {
	_attack = 5;
	_attackMode = 1;
	_mpConsumption = 1;
	/*_bullet = Sprite::create("Resources/Projectile.png");
	if (_bullet = nullptr) {
		log("Failed to initialize _bullet");
	}*/
	_bulletSpeed = 1000;
	this->setAnchorPoint(Vec2(0, 0));
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
	return true;
}

void Gun::fire(Scene* currentScene,const Vec2& pos) {
	//计算飞行方向和距离
	auto offset = pos - this->getPosition();
	offset.normalize();
	auto destination = offset * 2000;

	//子弹添加到枪口的位置，暂时设置为武器锚点的位置，后期改
	auto bullet = Sprite::create("Projectile.png");
	bullet->setScale(0.5);
	bullet->setPosition(Vec2(this->getPositionX(), this->getPositionY()));
	currentScene->addChild(bullet, 3);

	//创建子弹的动作
	auto bulletMove = MoveBy::create(2.0f, destination);
	auto actionRemove = RemoveSelf::create();
	
	//日志输出touch的坐标、武器初始坐标、子弹飞行方向
	log("Touch:x=%f, y=%f", pos.x, pos.y);
	log("Weapon:x=%f, y=%f", this->getPositionX(), this->getPositionY());
	log("Bullet:x=%f, y=%f", bullet->getPositionX(), bullet->getPositionY());
	log("Direction:x=%f, y=%f", offset.x, offset.y);

	//发射子弹
	bullet->runAction(Sequence::create(bulletMove, actionRemove, nullptr));
}