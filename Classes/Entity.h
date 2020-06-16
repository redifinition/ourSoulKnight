#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "cocos2d.h"
#include "Controller.h"
#include "ControllerListener.h"
using namespace cocos2d;
class Entity :public Node,public ControllerListener
{
public:
//by lq
	void bind_sprite(Sprite* sprite);//°ó¶¨Ò»¸ö¾«Áé¶ÔÏó
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
