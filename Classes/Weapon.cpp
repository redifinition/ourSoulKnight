#include "Weapon.h"

/*
Weapon* Weapon::create(const std::string& filename)
{
	Weapon* sprite = new Weapon;
	if (sprite && sprite->init(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Weapon::init(const std::string& filename)
{
	if (!Sprite::initWithFile(filename)) {
		return false;
	}
	return true;
}
*/
void Weapon::trackTouch() {

}
void Weapon::fire(Scene* currentScene,const Vec2& pos)
{

}