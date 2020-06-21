#include "Knight.h"


Knight::Knight()
{
	_HP = 5;
	_MP = 180;
	_AC = 5;
	_weaponPosition = Vec2(0.6, 0.25);
}

Knight::~Knight() {

}
bool Knight::init()
{
	return true;
}

void Knight::skill() {

}