#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "cocos2d.h"
#include "Controller.h"
#include "ControllerListener.h"
using namespace cocos2d;

class Entity :public Node,public ControllerListener
{
//by lzy
	CC_SYNTHESIZE(Sprite*, m_sprite, Sprite);
public:
//by lzy
	Entity();
	~Entity();
//by lzy
	bool bindSprite(Sprite* sprite);//°ó¶¨Ò»¸ö¾«Áé¶ÔÏó
//by lq
	//ÉèÖÃ¿ØÖÆÆ÷
	void set_controller(My_Controller* controller);
	//ÊµÏÖSimpleMoveListenerµÄ·½·¨
	virtual void set_tag_position(int x, int y);
	virtual Point get_tag_position();
protected:
//by lq
	Sprite* m_sprite;
	My_Controller* m_controller;

};
#endif
