#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "cocos2d.h"
using namespace cocos2d;
class Entity :public Node {
	CC_SYNTHESIZE(Sprite*, m_sprite, Sprite);
public:
	Entity();
	~Entity();
	bool bindSprite(Sprite* sprite);
};
#endif
