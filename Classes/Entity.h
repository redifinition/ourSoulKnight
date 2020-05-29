#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "cocos2d.h"
using namespace cocos2d;
class Entity :public Node
{
public:
	void bind_sprite(Sprite* sprite);//绑定一个精灵对象
protected:
	Sprite* m_sprite;
};



#endif
