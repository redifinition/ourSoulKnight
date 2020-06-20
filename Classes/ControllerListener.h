#ifndef  _CONTROLLERLISTENER_H
#define _CONTROLLERLISTENER_H

#include "cocos2d.h"
using namespace cocos2d;


class ControllerListener
{
public:
	//设置目标坐标
	virtual void set_tag_position(int x, int y) = 0;

	//获取目标坐标
	virtual Point get_tag_position() = 0;

};

#endif
#pragma once
