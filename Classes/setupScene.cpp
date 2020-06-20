#include "setupScene.h"
#include "ui/CocosGUI.h"
#include"MyHelloWorldScene.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include"safetymapScene.h"
#include"audio.h"
#include"startmapScene.h"

using namespace cocos2d::ui;
USING_NS_CC;


Scene* setup::createScene()
{
	return setup::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool setup::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object

	auto StartPicture = Sprite::create("startmenu.png");
	StartPicture->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	auto size = StartPicture->getContentSize();
	float scaleX = visibleSize.width / size.width;
	float scaleY = visibleSize.height / size.height;
	float scale = scaleX > scaleY ? scaleX : scaleY;
	StartPicture->setScale(scale);
	this->addChild(StartPicture, 1);

	//创建一个“元气骑士”标题的精灵，该精灵可以移动
	auto game_label = Sprite::create("gamelabel.png");
	game_label->setScale(0.65);
	game_label->setPosition(Vec2(100, visibleSize.height - 18));
	this->addChild(game_label,2);

	auto label_moveBy = MoveBy::create(0.3, Vec2(40, 0));
	game_label->runAction(label_moveBy);

	auto setup_background = Sprite::create("setupbackground.png");
	setup_background->setScaleX(1.15);//横向拉伸
	setup_background->setPosition(Vec2(-12, origin.y + visibleSize.height - 70));//初始位置在界面之外
	this->addChild(setup_background,2);
	auto background_moveBy = MoveBy::create(0.3, Vec2(35, 0));
	setup_background->runAction(background_moveBy);



	auto setup_button = MenuItemImage::create(
		"setupbutton.png",
		"setupbutton1.png",
		CC_CALLBACK_1(setup::menuCloseCallback, this));
	setup_button->setScale(10000);
	if (setup_button == nullptr ||
		setup_button->getContentSize().width <= 0 ||
		setup_button->getContentSize().height <= 0)
	{
		problemLoading("'setupbutton.png' and 'setupbutton1.png'");
	}
	else
	{

		setup_button->setPosition(Vec2(visibleSize.width / 20 + origin.x, visibleSize.height / 3 + origin.y));
	}


	// create menu, it's an autorelease object
	auto menu = Menu::create(setup_button, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 0);
	//音乐关button
	auto audio_button = Button::create("audiobutton_on.png", "audiobutton_off.png");
	audio_button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{

		audio_begin->pauseBackgroundMusic();;
		break;
		}
		default:
			break;
		}
	});
	audio_button->setScale(0.26);
	audio_button->setPosition(Vec2(-12, origin.y + 120));
	auto audio_moveBy = MoveBy::create(0.3, Vec2(36, 0));
	audio_button->runAction(audio_moveBy);

	this->addChild(audio_button,3);

	auto music_off_label = Label::createWithTTF("music off", "fonts/Marker Felt.ttf",8);
	if (music_off_label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		music_off_label->setPosition(Vec2(-12, origin.y + 135));
		auto label1_moveBy = MoveBy::create(0.3, Vec2(36, 0));
		music_off_label->runAction(label1_moveBy);
		this->addChild(music_off_label, 3);
	}

	//音乐开button
	auto audio_button_on = Button::create("audiobutton_on.png", "audiobutton_off.png");
	audio_button_on->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{

			audio_begin->resumeBackgroundMusic();
			break;
		}
		default:
			break;
		}
	});
	audio_button_on->setScale(0.26);
	audio_button_on->setPosition(Vec2(-12, origin.y + 155));
	auto audio_on_moveBy = MoveBy::create(0.3, Vec2(36, 0));
	audio_button_on->runAction(audio_on_moveBy);
	this->addChild(audio_button_on,3);
	//音乐开启标签
	auto music_on_label = Label::createWithTTF("music on", "fonts/Marker Felt.ttf", 8);
	if (music_off_label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		music_on_label->setPosition(Vec2(-12, origin.y + 170));
		auto label2_moveBy = MoveBy::create(0.3, Vec2(36, 0));
		music_on_label->runAction(label2_moveBy);
		this->addChild(music_on_label, 3);
	}
	//创建点击触发音量控制的按钮
	auto volume_button = MenuItemImage::create(
		"volumecontrol1.png",
		"volumecontrol2.png",
		CC_CALLBACK_1(setup::audio_menuCloseCallback, this));
	volume_button->setScale(0.095);
	if (volume_button == nullptr ||
		volume_button->getContentSize().width <= 0 ||
		volume_button->getContentSize().height <= 0)
	{
		problemLoading("'volumecontrol1.png' and 'volumecontrol2.png'");
	}
	else
	{

		volume_button->setPosition(Vec2(-12, origin.y + 190));
	}

	auto label3_moveBy = MoveBy::create(0.3, Vec2(36, 0));
	volume_button->runAction(label3_moveBy);
	// create menu, it's an autorelease object
	auto menu_volume = Menu::create(volume_button, NULL);
	menu_volume->setPosition(Vec2::ZERO);
	this->addChild(menu_volume, 3);
	
	//新游戏
	auto newGameItem = MenuItemImage::create(
		"newgamebutton1.png",
		"newgamebutton2.png",
		CC_CALLBACK_1(setup::newgame_menuCloseCallback, this));
	newGameItem->setScale(0.65);
	if (newGameItem == nullptr ||
		newGameItem->getContentSize().width <= 0 ||
		newGameItem->getContentSize().height <= 0)
	{
		problemLoading("'newgamebutton1.png' and 'newgamebutton2.png'");
	}
	else
	{
		newGameItem->setPosition(Vec2(visibleSize.width / 4 + 10 + origin.x, visibleSize.height / 8 + origin.y - 3));
	}
	auto menu1 = Menu::create(newGameItem, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, 3);

	return true;
}


void setup::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.7f, MyHelloWorld::createScene()));
}

void setup::volume_menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(setup::createScene());
}
void setup::audio_menuCloseCallback(Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto music_slider = Slider::create();
		music_slider->loadBarTexture("sliderback.png");
		music_slider->loadSlidBallTextures("slider_normal.png", "slider_press.png", "slider_disable.png");
		music_slider->loadProgressBarTexture("sliderpressbar.png");
		//获取音乐音量
		float music_percent = UserDefault::getInstance()->getFloatForKey("music_percent");
		//第一次默认音量值为100
		if (music_percent == 0.0f)
		{
			music_percent = 100.0f;
		}
		music_slider->setPercent(music_percent);
		music_slider->setScale(0.3);
		music_slider->setPosition(Vec2(-100, origin.y + visibleSize.height / 2));
		auto slider_moveto = MoveTo::create(0.4, Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2+5));
		music_slider->runAction(slider_moveto);

		//添加一个监听器
		music_slider->addEventListener([=](Ref* pSender, Slider::EventType type)
		{
			//当滑块的百分比发生变化时
			if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
			{
				int percent = music_slider->getPercent();
				SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(float(percent) / 100);
				audio_percent = (float)percent;
				UserDefault::getInstance()->setFloatForKey("musicPercent", percent);
			}
		});
		this->addChild(music_slider,5);
	//创建音量调节大小界面背景
	auto volume_background = Sprite::create("volume_background.png");
	volume_background->setScaleX(0.5);
	volume_background->setScaleY(0.4);
	volume_background->setPosition(-100, origin.y + visibleSize.height / 2);//先设置在看不见的地方
	auto volume_action = MoveTo::create(0.4, Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	volume_background->runAction(volume_action);
	this->addChild(volume_background, 4);

	//创建保存并返回的按钮
	auto reservation = MenuItemImage::create(
		"reservation.png",
		"reservation.png",
		CC_CALLBACK_1(setup::volume_menuCloseCallback, this));
	reservation->setScale(0.4);
	if (reservation == nullptr ||
		reservation->getContentSize().width <= 0 ||
		reservation->getContentSize().height <= 0)
	{
		problemLoading("'reservation1.png' and 'reservation2.png'");
	}
	else
	{
		reservation->setPosition(Vec2(-25, visibleSize.height / 2 + origin.y - 18));
	}
	auto menu = Menu::create(reservation, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 5);
	auto reservation_moveto = MoveTo::create(0.4, Vec2(visibleSize.width / 2 + origin.x + 75, visibleSize.height / 2 + origin.y - 18));
	reservation->runAction(reservation_moveto);
}


void setup::newgame_menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(startmap::createScene());
	//接口，进入到游戏安全地图中
	//记得关掉开场音乐
}

