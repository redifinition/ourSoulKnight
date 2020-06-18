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

void Weapon::hide() {
	this->setVisible(false);
}

void Weapon::show() {
	this->setVisible(true);
}

void Weapon::fire(Scene* _currentScene, const Vec2& pos) {

}