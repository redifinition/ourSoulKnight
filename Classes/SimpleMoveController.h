#ifndef _SIMPLEMOVECONTROLLER_H_
#define _SIMPLEMOVECONTROLLER_H_


#include "cocos2d.h"
#include "Controller.h"
using namespace cocos2d;

class SimpleMoveController :public My_Controller
{
public:
	CREATE_FUNC(SimpleMoveController);
	virtual bool init();
	virtual void update(float dt);

	void set_speed(int ispeed);//设置移动速度
private:
	int m_ispeed;

};

#endif