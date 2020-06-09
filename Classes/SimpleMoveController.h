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
	void set_ixspeed(int ispeed);
	void set_iyspeed(int ispeed);
	void bind_sprite(Sprite* sprite);


private:
	int m_ixspeed;//x方向的移动速度
	int m_iyspeed;//y方向的移动速度
	Sprite* m_sprite;
	void registeKeyBoardEvent();
	ValueMap   map;

	/*action management*/
	Animation* knight_animation_right_running;
	Animate* animate_knight_right_running;

	Animation* knight_animation_right_standing;
	Animate* animate_knight_right_standing;

	Animation* knight_animation_left_running;
	Animate* animate_knight_left_running;

	Animation* knight_animation_left_standing;
	Animate* animate_knight_left_standing;

	bool right_running_flag;
	bool right_standing_flag;
	bool left_running_flag;
	bool left_standing_flag;
	int right_left_flag;//to decide which action to use when running up and down
	bool key_w;
	bool key_d;
	bool key_a;
	bool key_s;
};

#endif