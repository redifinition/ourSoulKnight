#include "KnightInformationScene.h"
#include "startmapScene.h"
#include "audio.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* startmap::createScene()
{
	return startmap::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool startmap::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*stop the start music*/

	audio_begin->stopBackgroundMusic();
	audio_home->playBackgroundMusic("home_music.mp3",true);
	//SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(float(audio_percent) / 100);

	std::string floor_layer_file = "safetymap.tmx";//µØÍ¼ÎÄ¼þ
	_safetymap = TMXTiledMap::create(floor_layer_file);
	_safetymap->setAnchorPoint(Vec2::ZERO);
	_safetymap->setPosition(Vec2(-110,-720));
	TMXLayer* meta = _safetymap->getLayer("meta");
	meta->setVisible(false);
	
	/*create the knight's button*/
	auto knight_button = MenuItemImage::create(
		"standing_right_1_adjusted.png",
		"standing_right_1_adjusted.png",
		CC_CALLBACK_1(startmap::menuCloseCallback, this));
	if (knight_button == nullptr ||
		knight_button->getContentSize().width <= 0 ||
		knight_button->getContentSize().height <= 0)
	{
		problemLoading("'standing_right_1_adjusted.png' and 'standing_right_2_adjusted.png'");
	}
	else
	{
		/*TMXObjectGroup* objGroup = _safetymap->getObjectGroup("objects_knight");//loading object layer
		ValueMap player_point_map = objGroup->getObject("knight");
		float playerX = player_point_map.at("x").asFloat();
		float playerY = player_point_map.at("y").asFloat();*/
		knight_button->setPosition(Vec2(visibleSize.width/2+origin.x+125,visibleSize.height/2+origin.y+30));
		
	}
	auto menu1 = Menu::create(knight_button, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, -1);//just a virtual button which is unvisible
	

	/*create button which send player to home scene*/
	auto home_button = MenuItemImage::create(
		"home_button1.png",
		"home_button2.png",
		CC_CALLBACK_1(startmap::menuCloseCallbackHome, this));
	if (home_button == nullptr ||
		home_button->getContentSize().width <= 0 ||
		home_button->getContentSize().height <= 0)
	{
		problemLoading("'home_button1.png' and 'home_button2.png'");
	}
	else
	{
		
		home_button->setPosition(Vec2(visibleSize.width /10 + origin.x, visibleSize.height / 10 + origin.y));

	}
	auto menu2 = Menu::create(home_button, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 1);//just a virtual button which is unvisible

	this->addChild(_safetymap,0);
	return true;
}


void startmap::menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(KnightInformation::createScene());
}

void startmap::menuCloseCallbackHome(cocos2d::Ref* pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}