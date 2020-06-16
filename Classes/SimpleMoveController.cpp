#include "SimpleMoveController.h"
#include <map>
#include "Player.h"

bool SimpleMoveController::init()
{
	this->m_ixspeed = 0;
	this->m_iyspeed = 0;

	right_running_flag = true;
	right_standing_flag = true;
	left_standing_flag = true;
	left_running_flag = true;

	key_w = false;
	key_d= false;
	key_a = false;
	key_s = false;


	registeKeyBoardEvent();//注册键盘控制事件
	this->scheduleUpdate();

	
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
			set_iyspeed(2);
			if (right_left_flag == 1)
			{

				if (animate_knight_right_standing)
				{
					m_sprite->stopAction(animate_knight_right_standing);
					right_standing_flag = true;
				}


				if (right_running_flag == true)
				{
					knight_animation_right_running = Animation::create();
					char nameSize[30] = { 0 };
					for (int i = 1; i <= 4; i++)
					{
						sprintf(nameSize, "running_right_%d.png", i);
						knight_animation_right_running->addSpriteFrameWithFile(nameSize);
					}
					knight_animation_right_running->setDelayPerUnit(0.08f);//设置动画帧时间间隔
					knight_animation_right_running->setLoops(-1);
					knight_animation_right_running->setRestoreOriginalFrame(true);
					animate_knight_right_running = Animate::create(knight_animation_right_running);
					m_sprite->runAction(animate_knight_right_running);

					right_running_flag = false;
				}

			}
			if (right_left_flag == 0)
			{
				if (animate_knight_left_standing)
				{
					m_sprite->stopAction(animate_knight_left_standing);
					left_standing_flag = true;
				}

				if (left_running_flag == true)
				{
					knight_animation_left_running = Animation::create();
					char nameSize[30] = { 0 };
					for (int i = 1; i <= 4; i++)
					{
						sprintf(nameSize, "running_left_%d.png", i);
						knight_animation_left_running->addSpriteFrameWithFile(nameSize);
					}
					knight_animation_left_running->setDelayPerUnit(0.08f);//设置动画帧时间间隔
					knight_animation_left_running->setLoops(-1);
					knight_animation_left_running->setRestoreOriginalFrame(true);
					animate_knight_left_running = Animate::create(knight_animation_left_running);
					m_sprite->runAction(animate_knight_left_running);

					left_running_flag = false;
				}
			}
			break;
		}
		case EventKeyboard::KeyCode::KEY_A://左方向键;
		{
			set_ixspeed(-2);

			key_a = true;//key a is pressed

			right_left_flag = 0;//to decide which action to use when pressed w or s

			if (animate_knight_left_standing)
			{
				m_sprite->stopAction(animate_knight_left_standing);
				left_standing_flag = true;
			}

			if (animate_knight_right_standing)
			{
				m_sprite->stopAction(animate_knight_right_standing);
				right_standing_flag = true;
			}

			if (left_running_flag = true)
			{
				knight_animation_left_running = Animation::create();
				char nameSize[30] = { 0 };
				for (int i = 1; i <= 4; i++)
				{
					sprintf(nameSize, "running_left_%d.png", i);
					knight_animation_left_running->addSpriteFrameWithFile(nameSize);
				}
				knight_animation_left_running->setDelayPerUnit(0.08f);//设置动画帧时间间隔
				knight_animation_left_running->setLoops(-1);
				knight_animation_left_running->setRestoreOriginalFrame(true);
				animate_knight_left_running = Animate::create(knight_animation_left_running);
				m_sprite->runAction(animate_knight_left_running);

				left_running_flag = false;

			}

			break;
		}

		case EventKeyboard::KeyCode::KEY_S://下方向键;
		{

			key_s = true;
			if (right_left_flag == 1)
			{

				if (animate_knight_right_standing)
				{
					m_sprite->stopAction(animate_knight_right_standing);
					right_standing_flag = true;
				}


				if (right_running_flag == true)
				{
					knight_animation_right_running = Animation::create();
					char nameSize[30] = { 0 };
					for (int i = 1; i <= 4; i++)
					{
						sprintf(nameSize, "running_right_%d.png", i);
						knight_animation_right_running->addSpriteFrameWithFile(nameSize);
					}
					knight_animation_right_running->setDelayPerUnit(0.08f);//设置动画帧时间间隔
					knight_animation_right_running->setLoops(-1);
					knight_animation_right_running->setRestoreOriginalFrame(true);
					animate_knight_right_running = Animate::create(knight_animation_right_running);
					m_sprite->runAction(animate_knight_right_running);

					right_running_flag = false;
				}

			}
			if (right_left_flag == 0)
			{
				if (animate_knight_left_standing)
				{
					m_sprite->stopAction(animate_knight_left_standing);
					left_standing_flag = true;
				}

				if (left_running_flag == true)
				{
					knight_animation_left_running = Animation::create();
					char nameSize[30] = { 0 };
					for (int i = 1; i <= 4; i++)
					{
						sprintf(nameSize, "running_left_%d.png", i);
						knight_animation_left_running->addSpriteFrameWithFile(nameSize);
					}
					knight_animation_left_running->setDelayPerUnit(0.08f);//设置动画帧时间间隔
					knight_animation_left_running->setLoops(-1);
					knight_animation_left_running->setRestoreOriginalFrame(true);
					animate_knight_left_running = Animate::create(knight_animation_left_running);
					m_sprite->runAction(animate_knight_left_running);

					left_running_flag = false;
				}
			}
			set_iyspeed(-2);
			break;
		}
		case EventKeyboard::KeyCode::KEY_D://右方向键;
		{
			key_d = true;
			right_left_flag = 1;
			if (animate_knight_right_standing)
			{
				m_sprite->stopAction(animate_knight_right_standing);
				right_standing_flag = true;
			}

			if (animate_knight_left_standing)
			{
				m_sprite->stopAction(animate_knight_left_standing);
				left_standing_flag = true;
			}
			if (right_running_flag == true)
			{
				knight_animation_right_running = Animation::create();
				char nameSize[30] = { 0 };
				for (int i = 1; i <= 4; i++)
				{
					sprintf(nameSize, "running_right_%d.png", i);
					knight_animation_right_running->addSpriteFrameWithFile(nameSize);
				}
				knight_animation_right_running->setDelayPerUnit(0.08f);//设置动画帧时间间隔
				knight_animation_right_running->setLoops(-1);
				knight_animation_right_running->setRestoreOriginalFrame(true);
				animate_knight_right_running = Animate::create(knight_animation_right_running);
				m_sprite->runAction(animate_knight_right_running);

				right_running_flag = false;
			}

			set_ixspeed(2);
			break;
		}

		}
	};

	keyBoardListener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_W:
		{
			auto y = m_sprite->getPositionY();
			key_w = false;
			if (right_left_flag == 1)
			{
				if (animate_knight_right_running&&key_d==false)
				{
					m_sprite->stopAction(animate_knight_right_running);
					right_running_flag =true;
				}

				/*start the standing_right action*/
				if (right_standing_flag == true&&key_d==false)
				{
					knight_animation_right_standing = Animation::create();
					char nameSize[30] = { 0 };
					for (int i = 1; i <= 2; i++)
					{
						sprintf(nameSize, "standing_right_%d_adjusted.png", i);
						knight_animation_right_standing->addSpriteFrameWithFile(nameSize);
					}
					knight_animation_right_standing->setDelayPerUnit(0.1f);//设置动画帧时间间隔
					knight_animation_right_standing->setLoops(-1);
					knight_animation_right_standing->setRestoreOriginalFrame(true);
					animate_knight_right_standing = Animate::create(knight_animation_right_standing);
					m_sprite->runAction(animate_knight_right_standing);

					right_standing_flag = false;
				}
			}

			if (right_left_flag ==0)
			{
				if (animate_knight_left_running&&key_a == false)
				{
					m_sprite->stopAction(animate_knight_left_running);
					left_running_flag = true;
				}

				/*start the standing_left action*/
				if (left_standing_flag == true && key_a == false)
				{
					knight_animation_left_standing = Animation::create();
					char nameSize[30] = { 0 };
					for (int i = 1; i <= 2; i++)
					{
						sprintf(nameSize, "standing_left_%d.png", i);
						knight_animation_left_standing->addSpriteFrameWithFile(nameSize);
					}
					knight_animation_left_standing->setDelayPerUnit(0.1f);//设置动画帧时间间隔
					knight_animation_left_standing->setLoops(-1);
					knight_animation_left_standing->setRestoreOriginalFrame(true);
					animate_knight_left_standing = Animate::create(knight_animation_left_standing);
					m_sprite->runAction(animate_knight_left_standing);

					left_standing_flag = false;
				}
			}
			set_iyspeed(0);
			break;
		}
		case EventKeyboard::KeyCode::KEY_A://左方向键;
		{
			key_a = false;//key a is released
			if (animate_knight_left_running&&key_w == false)
			{
				m_sprite->stopAction(animate_knight_left_running);
				left_running_flag = true;
			}

			if (left_standing_flag == true && key_w == false&&key_s==false)
			{
				knight_animation_left_standing = Animation::create();
				char nameSize[30] = { 0 };
				for (int i = 1; i <= 2; i++)
				{
					sprintf(nameSize, "standing_left_%d.png", i);
					knight_animation_left_standing->addSpriteFrameWithFile(nameSize);
				}
				knight_animation_left_standing->setDelayPerUnit(0.1f);//设置动画帧时间间隔
				knight_animation_left_standing->setLoops(-1);
				knight_animation_left_standing->setRestoreOriginalFrame(true);
				animate_knight_left_standing = Animate::create(knight_animation_left_standing);
				m_sprite->runAction(animate_knight_left_standing);
				left_standing_flag = false;
			}
			set_ixspeed(0);
			break;
		}
		case EventKeyboard::KeyCode::KEY_S://上方向键;
		{
			key_s = false;
			if (right_left_flag == 1)
			{
				if (animate_knight_right_running&&key_d == false)
				{
					m_sprite->stopAction(animate_knight_right_running);
					right_running_flag = true;
				}

				/*start the standing_right action*/
				if (right_standing_flag == true && key_d == false)
				{
					knight_animation_right_standing = Animation::create();
					char nameSize[30] = { 0 };
					for (int i = 1; i <= 2; i++)
					{
						sprintf(nameSize, "standing_right_%d_adjusted.png", i);
						knight_animation_right_standing->addSpriteFrameWithFile(nameSize);
					}
					knight_animation_right_standing->setDelayPerUnit(0.1f);//设置动画帧时间间隔
					knight_animation_right_standing->setLoops(-1);
					knight_animation_right_standing->setRestoreOriginalFrame(true);
					animate_knight_right_standing = Animate::create(knight_animation_right_standing);
					m_sprite->runAction(animate_knight_right_standing);

					right_standing_flag = false;
				}
			}

			if (right_left_flag == 0)
			{
				if (animate_knight_left_running&&key_a == false)
				{
					m_sprite->stopAction(animate_knight_left_running);
					left_running_flag = true;
				}

				/*start the standing_left action*/
				if (left_standing_flag == true && key_a == false)
				{
					knight_animation_left_standing = Animation::create();
					char nameSize[30] = { 0 };
					for (int i = 1; i <= 2; i++)
					{
						sprintf(nameSize, "standing_left_%d.png", i);
						knight_animation_left_standing->addSpriteFrameWithFile(nameSize);
					}
					knight_animation_left_standing->setDelayPerUnit(0.1f);//设置动画帧时间间隔
					knight_animation_left_standing->setLoops(-1);
					knight_animation_left_standing->setRestoreOriginalFrame(true);
					animate_knight_left_standing = Animate::create(knight_animation_left_standing);
					m_sprite->runAction(animate_knight_left_standing);

					left_standing_flag = false;
				}
			}
			set_iyspeed(0);
			break;
		}

		case EventKeyboard::KeyCode::KEY_D://右方向键;
		{
			key_d = false;//key d is released

			if (animate_knight_right_running&&key_w==false)
			{
				m_sprite->stopAction(animate_knight_right_running);
			    right_running_flag = true;
			}

			if (right_standing_flag == true&&key_w==false&&key_s==false)
			{
				knight_animation_right_standing = Animation::create();
				char nameSize[30] = { 0 };
				for (int i = 1; i <= 2; i++)
				{
					sprintf(nameSize, "standing_right_%d_adjusted.png", i);
					knight_animation_right_standing->addSpriteFrameWithFile(nameSize);
				}
				knight_animation_right_standing->setDelayPerUnit(0.1f);//设置动画帧时间间隔
				knight_animation_right_standing->setLoops(-1);
				knight_animation_right_standing->setRestoreOriginalFrame(true);
				animate_knight_right_standing = Animate::create(knight_animation_right_standing);
				m_sprite->runAction(animate_knight_right_standing);
				right_standing_flag =false;
			}

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

