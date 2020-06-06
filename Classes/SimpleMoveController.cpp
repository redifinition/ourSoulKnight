#include "SimpleMoveController.h"
#include <map>
#include "Player.h"

bool SimpleMoveController::init()
{
	this->m_ixspeed = 0;
	this->m_iyspeed = 0;

	registeKeyBoardEvent();//注册键盘控制事件
	this->scheduleUpdate();

	return true;
}

void SimpleMoveController::update(float dt)
{
	if (m_controllerListener == NULL)
		return;
	//键盘控制实现
	//增加移动对象的X坐标值
	Point pos = m_controllerListener->get_tag_position();
	pos.x += m_ixspeed;
	pos.y += m_iyspeed;
	m_controllerListener->set_tag_position(pos.x, pos.y);

}

void SimpleMoveController::set_speed(int ispeed)
{
	this->m_ixspeed = ispeed;
}

void SimpleMoveController::set_ixspeed(int ispeed)
{
	this->m_ixspeed = ispeed;
}

void SimpleMoveController::set_iyspeed(int ispeed)
{
	this->m_iyspeed = ispeed;
}

//键盘控制实现
void SimpleMoveController::registeKeyBoardEvent()
{


	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_W://上方向键;
			set_iyspeed(2);
			break;
		case EventKeyboard::KeyCode::KEY_A://左方向键;
			set_ixspeed(-2);
			break;
		case EventKeyboard::KeyCode::KEY_S://右方向键;
			set_iyspeed(-2);
			break;
		case EventKeyboard::KeyCode::KEY_D://下方向键;
			set_ixspeed(2);
			break;

		}
	};

	keyBoardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_W:
			set_iyspeed(0);
			break;
		case EventKeyboard::KeyCode::KEY_A://上方向键;
			set_ixspeed(0);
			break;
		case EventKeyboard::KeyCode::KEY_S://上方向键;
			set_iyspeed(0);
			break;
		case EventKeyboard::KeyCode::KEY_D://上方向键;
			set_ixspeed(0);
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);

}

