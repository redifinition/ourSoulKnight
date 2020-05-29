#include "HelloWorldScene.h"
#include "MyHelloWorldScene.h"
#include "audio.h"
#include "safetymapScene.h"
#include "Player.h"

USING_NS_CC;

Scene* safetymap::createScene()
{
	return safetymap::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool safetymap::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//创建地图背景

	std::string floor_layer_file = "myfirstmap.tmx";//地板文件
	_tiledmap = TMXTiledMap::create(floor_layer_file);
	//_tiledmap->setScale(0.2);




	//添加player
	auto pinfo = AutoPolygon::generatePolygon("player.png");
	Sprite* player_sprite = Sprite::create(pinfo);
	Player* mplayer = Player::create();
	mplayer->bind_sprite(player_sprite);
	mplayer->run();
	TMXObjectGroup* objGroup = _tiledmap->getObjectGroup("knight");//加载对象层
	//加载玩家坐标对象
	ValueMap player_point_map = objGroup->getObject("PlayerPoint");
	float playerX = player_point_map.at("x").asFloat();
	float playerY = player_point_map.at("y").asFloat();

	//设置玩家坐标
	mplayer->setPosition(Vec2(visibleSize.width/2-100, visibleSize.height/2));

	this->addChild(mplayer,1);

	this->addChild(_tiledmap, -1);
	return true;
}

/*void safetymap::add_player(TMXTiledMap* map)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//创建一个精灵
	Sprite* player_sprite = Sprite::create("player.png");
	Player* mplayer = Player::create();
	mplayer->bind_sprite(player_sprite);
	mplayer->run();

    //设置玩家坐标
	mplayer->setPosition(Vec2(100, visibleSize.height / 2));

	_tiledmap->addChild(mplayer);
}*/
