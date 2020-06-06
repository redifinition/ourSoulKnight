#include "Entity.h"

Entity::Entity() {
	m_sprite = NULL;
}

Entity::~Entity() {
}

bool Entity::bindSprite(Sprite*sprite) {
	this->m_sprite = sprite;
	if (m_sprite == nullptr)
	{
		printf("m_sprite in this entity is nullptr, check wether the file used to create the sprite in right dictionary.");
		return false;
	}
	else
	{
		this->addChild(m_sprite);

		/*设置Entity的大小和m_sprite的大小一致，否则碰撞模型会不对*/
		Size size = m_sprite->getContentSize();
		this->setContentSize(size);
		m_sprite->setPosition(Point(size.width*0.5f, size.height*0.5f));

		return true;
	}
}