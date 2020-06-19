#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "cocos2d.h"
#include "ControllerListener.h"

using namespace cocos2d;

class My_Controller :public Node
{
public:
	/*…Ë÷√º‡Ã˝∂‘œÛ*/
	void set_controller_listener(ControllerListener* controllerListener);
protected:
	ControllerListener* m_controllerListener;
};

#endif
#pragma once