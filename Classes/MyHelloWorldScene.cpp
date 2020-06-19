#include "MyHelloWorldScene.h"
#include"setupScene.h"
#include"AppDelegate.h"
#include "startmapScene.h"

#include "ui/CocosGUI.h"
#include "cocos2d.h"

using namespace cocos2d::ui;
USING_NS_CC;

Scene* MyHelloWorld::createScene()
{
	return MyHelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MyHelloWorld::init()
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
	this->addChild(StartPicture, 0);

	//创建一个“元气骑士”标题的精灵，该精灵可以移动
	auto game_label = Sprite::create("gamelabel.png");
	game_label->setScale(0.65);
	game_label->setPosition(Vec2(100, visibleSize.height - 18));
	this->addChild(game_label);

	auto setup_button = MenuItemImage::create(
		"setupbutton.png",
		"setupbutton1.png",
		CC_CALLBACK_1(MyHelloWorld::menuCloseCallback, this));
	setup_button->setScale(0.3);
	if (setup_button == nullptr ||
		setup_button->getContentSize().width <= 0 ||
		setup_button->getContentSize().height <= 0)
	{
		problemLoading("'setupbutton.png' and 'setupbutton.png'");
	}
	else
	{

		setup_button->setPosition(Vec2(visibleSize.width / 20 + origin.x, visibleSize.height / 3 + origin.y));
	}
	auto menu = Menu::create(setup_button, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto newGameItem = MenuItemImage::create(
		"newgamebutton1.png",
		"newgamebutton2.png",
		CC_CALLBACK_1(MyHelloWorld::newgame_menuCloseCallback, this));
	newGameItem->setScale(0.65);
	if (newGameItem == nullptr ||
		newGameItem->getContentSize().width <= 0 ||
		newGameItem->getContentSize().height <= 0)
	{
		problemLoading("'newgamebutton1.png' and 'newgamebutton2.png'");
	}
	else
	{
		newGameItem->setPosition(Vec2(visibleSize.width / 4+10 + origin.x, visibleSize.height / 8+ origin.y-3));
	}
	auto menu1 = Menu::create(newGameItem, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, 1);


	return true;
}


void MyHelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(setup::createScene());
}

void MyHelloWorld::newgame_menuCloseCallback(Ref* pSender)
{
	//接口，进入到游戏安全地图中
	Director::getInstance()->replaceScene(startmap::createScene());
}

