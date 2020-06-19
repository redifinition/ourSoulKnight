
#include"KnightInformationScene.h"
#include"KnightStartMapScene.h"
#include"startmapScene.h"
USING_NS_CC;

Scene* KnightInformation::createScene()
{
	return KnightInformation::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in KnightInformationScene.cpp\n");
}

// on "init" you need to initialize your instance
bool KnightInformation::init()
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
	/*add the knight data page*/
	auto knight_data = Sprite::create("knight_data_page.png");
	knight_data->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	knight_data->setScale(0.65);

	/*add the start game virtual button*/
	auto knight_start_button = MenuItemImage::create(
		"start_knight.png",
		"start_knight.png",
		CC_CALLBACK_1(KnightInformation::menuCloseCallback, this));
	if (knight_start_button == nullptr ||
		knight_start_button->getContentSize().width <= 0 ||
		knight_start_button->getContentSize().height <= 0)
	{
		problemLoading("'start_knight.png'");
	}
	else
	{

		knight_start_button->setPosition(Vec2(visibleSize.width / 2 + origin.x + 150, visibleSize.height / 4 + origin.y - 30));
		knight_start_button->setScale(1.2);
	}
	auto menu1 = Menu::create(knight_start_button, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1,-1);//just a virtual button which is unvisible

	/* add the start game button*/
	auto start_button = Sprite::create("start_knight.png");
	start_button->setPosition(visibleSize.width / 2 + origin.x+150, visibleSize.height / 4 + origin.y-30);
	auto scale_smaller = ScaleTo::create(0.4f, 0.8f, 0.8f);
	auto scale_bigger = ScaleTo::create(0.4f, 1.25f, 1.25f);
	auto sequence = Sequence::create(scale_smaller, scale_bigger, nullptr);
	start_button->runAction(RepeatForever::create(sequence));

	/*add the close button*/
	auto knight_close_button = MenuItemImage::create(
		"knight_close_button1.png",
		"knight_close_button2.png",
		CC_CALLBACK_1(KnightInformation::close_menuCloseCallback, this));
	if (knight_close_button == nullptr ||
		knight_close_button->getContentSize().width <= 0 ||
		knight_close_button->getContentSize().height <= 0)
	{
		problemLoading("'close_knight.png'");
	}
	else
	{

		knight_close_button->setPosition(Vec2(visibleSize.width / 2 + origin.x - 150, visibleSize.height / 4 + origin.y - 30));
		knight_close_button->setScale(0.4);
	}
	auto menu2 = Menu::create(knight_close_button, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 1);//just a virtual button which is unvisible


	this->addChild(start_button,1);

	this->addChild(knight_data, 0);

	return true;
}

void KnightInformation::menuCloseCallback(cocos2d::Ref* pSender)
{
   Director::getInstance()->replaceScene(KnightStartMap::createScene());
}

void KnightInformation::close_menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(startmap::createScene());
}


