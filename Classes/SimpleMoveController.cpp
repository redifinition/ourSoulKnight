#include "SimpleMoveController.h"

bool SimpleMoveController::init()
{
	this->m_ispeed = 0;

	this->scheduleUpdate();

	return true;
}

void SimpleMoveController::update(float dt)
{
	if (m_controllerListener == NULL)
		return;

	//增加移动对象的X坐标值
	Point pos = m_controllerListener->get_tag_position();
	pos.x += m_ispeed;
	m_controllerListener->set_tag_position(pos.x, pos.y);

}

void SimpleMoveController::set_speed(int ispeed)
{
	this->m_ispeed = ispeed;
}