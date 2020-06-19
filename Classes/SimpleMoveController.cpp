#include "SimpleMoveController.h"
#include <map>
#include "Player.h"

bool SimpleMoveController::init()
{
	this->m_ixspeed = 0;
	this->m_iyspeed = 0;


	registeKeyBoardEvent();//注册键盘控制事件
	this->scheduleUpdate();

	key_w = false;
	key_a = false;
	key_s = false;
	key_d = false;

	return true;
}

void SimpleMoveController::update(float dt)
{
	if (m_controllerListener == NULL)
		return;
	//键盘控制实现
	//增加移动对象的X坐标值
	Point pos = m_controllerListener->get_tag_position();
	pos.x += m_ixspeed;
	pos.y += m_iyspeed;
	m_controllerListener->set_tag_position(pos.x, pos.y);

}

void SimpleMoveController::set_speed(int ispeed)
{
	this->m_ixspeed = ispeed;
}

void SimpleMoveController::set_ixspeed(int ispeed)
{
	this->m_ixspeed = ispeed;
}

void SimpleMoveController::set_iyspeed(int ispeed)
{
	this->m_iyspeed = ispeed;
}

//键盘控制实现

/*伪代码

*/
void SimpleMoveController::registeKeyBoardEvent()
{


	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_W://上方向键;
		{
			key_w = true;
			m_sprite->stopAllActions();
			if (left_right_tag == -1)
			{
				knight_animate = Animation::create();
				char nameSize[30] = { 0 };
				for (int i = 1; i <= 4; i++)
				{
					sprintf(nameSize, "running_left_%d.png", i);
					knight_animate->addSpriteFrameWithFile(nameSize);
				}
				knight_animate->setDelayPerUnit(0.08f);//设置动画帧时间间隔
				knight_animate->setLoops(-1);
				knight_animate->setRestoreOriginalFrame(true);
				knight_animate_run = Animate::create(knight_animate);
				m_sprite->runAction(knight_animate_run);
			}
			if (left_right_tag == 1)
			{
				knight_animate = Animation::create();
				char nameSize[30] = { 0 };
				for (int i = 1; i <= 4; i++)
				{
					sprintf(nameSize, "running_right_%d.png", i);
					knight_animate->addSpriteFrameWithFile(nameSize);
				}
				knight_animate->setDelayPerUnit(0.08f);//设置动画帧时间间隔
				knight_animate->setLoops(-1);
				knight_animate->setRestoreOriginalFrame(true);
				knight_animate_run = Animate::create(knight_animate);
				m_sprite->runAction(knight_animate_run);
			}
			set_iyspeed(2);


			break;
		}
		case EventKeyboard::KeyCode::KEY_A://左方向键;
		{
			set_ixspeed(-2);
			key_a = true;
			m_sprite->stopAllActions();

			knight_animate = Animation::create();
			char nameSize[30] = { 0 };
			for (int i = 1; i <= 4; i++)
			{
				sprintf(nameSize, "running_left_%d.png", i);
				knight_animate->addSpriteFrameWithFile(nameSize);
			}
			knight_animate->setDelayPerUnit(0.08f);//设置动画帧时间间隔
			knight_animate->setLoops(-1);
			knight_animate->setRestoreOriginalFrame(true);
			knight_animate_run = Animate::create(knight_animate);
			m_sprite->runAction(knight_animate_run);

			left_right_tag = -1;
			break;

		}

		case EventKeyboard::KeyCode::KEY_S://下方向键;
		{
			key_s = true;
			m_sprite->stopAllActions();
			if (left_right_tag == -1)
			{
				knight_animate = Animation::create();
				char nameSize[30] = { 0 };
				for (int i = 1; i <= 4; i++)
				{
					sprintf(nameSize, "running_left_%d.png", i);
					knight_animate->addSpriteFrameWithFile(nameSize);
				}
				knight_animate->setDelayPerUnit(0.08f);//设置动画帧时间间隔
				knight_animate->setLoops(-1);
				knight_animate->setRestoreOriginalFrame(true);
				knight_animate_run = Animate::create(knight_animate);
				m_sprite->runAction(knight_animate_run);
			}
			if (left_right_tag == 1)
			{
				knight_animate = Animation::create();
				char nameSize[30] = { 0 };
				for (int i = 1; i <= 4; i++)
				{
					sprintf(nameSize, "running_right_%d.png", i);
					knight_animate->addSpriteFrameWithFile(nameSize);
				}
				knight_animate->setDelayPerUnit(0.08f);//设置动画帧时间间隔
				knight_animate->setLoops(-1);
				knight_animate->setRestoreOriginalFrame(true);
				knight_animate_run = Animate::create(knight_animate);
				m_sprite->runAction(knight_animate_run);
			}

			set_iyspeed(-2);
			break;
		}
		case EventKeyboard::KeyCode::KEY_D://右方向键;
		{
			key_d = true;
			m_sprite->stopAllActions();
			knight_animate = Animation::create();
			char nameSize[30] = { 0 };
			for (int i = 1; i <= 4; i++)
			{
				sprintf(nameSize, "running_right_%d.png", i);
				knight_animate->addSpriteFrameWithFile(nameSize);
			}
			knight_animate->setDelayPerUnit(0.08f);//设置动画帧时间间隔
			knight_animate->setLoops(-1);
			knight_animate->setRestoreOriginalFrame(true);
			knight_animate_run = Animate::create(knight_animate);
			m_sprite->runAction(knight_animate_run);

			left_right_tag = 1;
			set_ixspeed(2);
			break;
		}

		}
	};

	keyBoardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_W:
		{
			if (key_a == false && key_s == false && key_d == false)
			{
				m_sprite->stopAllActions();
				if (left_right_tag == -1)
				{
					knight_animate = Animation::create();
					char nameSize[30] = { 0 };
					for (int i = 1; i <= 2; i++)
					{
						sprintf(nameSize, "standing_left_%d.png", i);
						knight_animate->addSpriteFrameWithFile(nameSize);
					}
					knight_animate->setDelayPerUnit(0.1f);//设置动画帧时间间隔
					knight_animate->setLoops(-1);
					knight_animate->setRestoreOriginalFrame(true);
					knight_animate_run = Animate::create(knight_animate);
					m_sprite->runAction(knight_animate_run);
				}
				if (left_right_tag == 1)
				{
					knight_animate = Animation::create();
					char nameSize[30] = { 0 };
					for (int i = 1; i <= 2; i++)
					{
						sprintf(nameSize, "standing_right_%d_adjusted.png", i);
						knight_animate->addSpriteFrameWithFile(nameSize);
					}
					knight_animate->setDelayPerUnit(0.1f);//设置动画帧时间间隔
					knight_animate->setLoops(-1);
					knight_animate->setRestoreOriginalFrame(true);
					knight_animate_run = Animate::create(knight_animate);
					m_sprite->runAction(knight_animate_run);
				}
			}
			key_w = false;
			set_iyspeed(0);
			break;
		}
		case EventKeyboard::KeyCode::KEY_A://左方向键;
		{
			if (key_w == false && key_s == false && key_d == false)
			{
				m_sprite->stopAllActions();
				knight_animate = Animation::create();
				char nameSize[30] = { 0 };
				for (int i = 1; i <= 2; i++)
				{
					sprintf(nameSize, "standing_left_%d.png", i);
					knight_animate->addSpriteFrameWithFile(nameSize);
				}
				knight_animate->setDelayPerUnit(0.1f);//设置动画帧时间间隔
				knight_animate->setLoops(-1);
				knight_animate->setRestoreOriginalFrame(true);
				knight_animate_run = Animate::create(knight_animate);
				m_sprite->runAction(knight_animate_run);
			}
			key_a = false;
			set_ixspeed(0);
			break;
		}
		case EventKeyboard::KeyCode::KEY_S://下方向键;
		{
			if (key_w == false && key_a == false && key_d == false)
			{
				m_sprite->stopAllActions();
				if (left_right_tag == -1)
				{
					knight_animate = Animation::create();
					char nameSize[30] = { 0 };
					for (int i = 1; i <= 2; i++)
					{
						sprintf(nameSize, "standing_left_%d.png", i);
						knight_animate->addSpriteFrameWithFile(nameSize);
					}
					knight_animate->setDelayPerUnit(0.1f);//设置动画帧时间间隔
					knight_animate->setLoops(-1);
					knight_animate->setRestoreOriginalFrame(true);
					knight_animate_run = Animate::create(knight_animate);
					m_sprite->runAction(knight_animate_run);
				}
				if (left_right_tag == 1)
				{
					knight_animate = Animation::create();
					char nameSize[30] = { 0 };
					for (int i = 1; i <= 2; i++)
					{
						sprintf(nameSize, "standing_right_%d_adjusted.png", i);
						knight_animate->addSpriteFrameWithFile(nameSize);
					}
					knight_animate->setDelayPerUnit(0.1f);//设置动画帧时间间隔
					knight_animate->setLoops(-1);
					knight_animate->setRestoreOriginalFrame(true);
					knight_animate_run = Animate::create(knight_animate);
					m_sprite->runAction(knight_animate_run);
				}
			}
			key_s = false;
			set_iyspeed(0);
			break;
		}

		case EventKeyboard::KeyCode::KEY_D://右方向键;
		{
			if (key_w == false && key_a == false && key_s == false)
			{
				m_sprite->stopAllActions();
				knight_animate = Animation::create();
				char nameSize[30] = { 0 };
				for (int i = 1; i <= 2; i++)
				{
					sprintf(nameSize, "standing_right_%d_adjusted.png", i);
					knight_animate->addSpriteFrameWithFile(nameSize);
				}
				knight_animate->setDelayPerUnit(0.1f);//设置动画帧时间间隔
				knight_animate->setLoops(-1);
				knight_animate->setRestoreOriginalFrame(true);
				knight_animate_run = Animate::create(knight_animate);
				m_sprite->runAction(knight_animate_run);
			}
			key_d = false;
			set_ixspeed(0);
			break;
		}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);



}

void SimpleMoveController::bind_sprite(Sprite* sprite)
{
	m_sprite = sprite;
}
