#include "HelloWorldScene.h"
#include "MyHelloWorldScene.h"
#include "safetymapScene.h"
//#include "SimpleAudioEngine.h"
#include "audio.h"
//using namespace CocosDenshion;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	audio_home->stopBackgroundMusic();
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto StartPicture = Sprite::create("START.png");
	StartPicture->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	auto size = StartPicture->getContentSize();
	float scaleX = visibleSize.width / size.width;
	float scaleY = visibleSize.height / size.height;
	float scale = scaleX > scaleY ? scaleX : scaleY;
	StartPicture->setScale(scale);
	this->addChild(StartPicture, 1);

	//因为cocos2d-x实现鼠标点击任意位置触发回调稍嫌麻烦，因此直接创建一个按钮置于底层，大小超过屏幕大小
	auto closeItem = MenuItemImage::create(
		"startbutton.png",
		"startbutton1.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setScale(10000);
	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'virtuallabel1.png' and 'virtuallabel2.png'");
	}
	else
	{
		closeItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 6 + origin.y));
	}
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 0);

	auto sprite = Sprite::create("1.png");
	sprite->setScale(0.3);//将开始键精灵缩放
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y));
	this->addChild(sprite,2);
	auto animation = Animation::create();
	char nameSize[20] = { 0 };
	for (int i = 1; i <= 16; i++)
	{
		sprintf(nameSize, "%d.png", i);
		animation->addSpriteFrameWithFile(nameSize);
	}
	animation->setDelayPerUnit(0.06f);//设置动画帧时间间隔
	animation->setLoops(-1);
	animation->setRestoreOriginalFrame(true);
	auto animate = Animate::create(animation);
	sprite->runAction(animate);
	//auto audio = SimpleAudioEngine::getInstance();
	audio_begin->playBackgroundMusic("startgame.mp3", true);


	//Director::getInstance()->replaceScene(TransitionCrossFade::create(0.7f, MyHelloWorld::createScene()));

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{

	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.7f, MyHelloWorld::createScene()));
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.7f, MyHelloWorld::createScene()));
	return true;
}

