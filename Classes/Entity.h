#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "cocos2d.h"
#include "Controller.h"
#include "ControllerListener.h"
using namespace cocos2d;
class Entity :public Node,public ControllerListener
{
public:
	void bind_sprite(Sprite* sprite);//��һ���������

	//���ÿ�����
	void set_controller(My_Controller* controller);

	//ʵ��SimpleMoveListener�ķ���
	virtual void set_tag_position(int x, int y);
	virtual Point get_tag_position();
protected:
	Sprite* m_sprite;
	My_Controller* m_controller;
 
};



#endif
