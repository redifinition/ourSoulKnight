#include "Entity.h"

void Entity::bind_sprite(Sprite* sprite)
{
	m_sprite = sprite;
	this->addChild(m_sprite);
}

void Entity::set_controller(My_Controller* controller)
{
	this->m_controller = controller;
	m_controller->set_controller_listener(this);
}


void Entity::set_tag_position(int x, int y)
{
	setPosition(Point(x, y));
}

Point Entity::get_tag_position()
{
	return getPosition();
}
