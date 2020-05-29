#include "Entity.h"

void Entity::bind_sprite(Sprite* sprite)
{
	m_sprite = sprite;
	this->addChild(m_sprite);
}