#include "HelloWorldScene.h"
#include "MyHelloWorldScene.h"
#include "audio.h"
#include "safetymapScene.h"
#include "SimpleMoveController.h"
#include "Controller.h"
#include "Player.h"
#include "Gun.h"
#include "RemoteSoldierManager.h"

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
	std::string floor_layer_file = "myfirstmap2.tmx";//地图文件
	_tiledmap = TMXTiledMap::create(floor_layer_file);
	_tiledmap->setAnchorPoint(Vec2::ZERO);
	_tiledmap->setPosition(Vec2::ZERO);
	


	//添加player
	//auto pinfo = AutoPolygon::generatePolygon("player.png");
	Sprite* player_sprite = Sprite::create("turn right 1.png");
	Player* mplayer = Player::create();
	//添加初始武器
	Gun* initialWeapon = Gun::create("broken pistol.png");
	mplayer->bindSprite(player_sprite);
	mplayer->bindWeapon(initialWeapon);
	mplayer->setTiledMap(_tiledmap);

	TMXObjectGroup* objGroup = _tiledmap->getObjectGroup("objects");//加载对象层

	//加载玩家坐标对象
	ValueMap player_point_map = objGroup->getObject("PlayerPoint");
	float playerX = player_point_map.at("x").asFloat();
	float playerY = player_point_map.at("y").asFloat();

	//设置玩家坐标
	mplayer->setPosition(Point(playerX,playerY));


	//创建怪物
	RemoteSoldierManager* remoteSoldierManager = RemoteSoldierManager::create(this, mplayer, _tiledmap);
	this->addChild(remoteSoldierManager);

	auto knight_animation = Animation::create();
	char nameSize[30] = { 0 };
	for (int i = 1; i <= 4; i++)
	{
		sprintf(nameSize, "turn right %d.png", i);
		knight_animation->addSpriteFrameWithFile(nameSize);
	}
	knight_animation->setDelayPerUnit(0.08f);//设置动画帧时间间隔
	knight_animation->setLoops(-1);
	knight_animation->setRestoreOriginalFrame(true);
	Animate* animate_knight = Animate::create(knight_animation);
	player_sprite->runAction(animate_knight);

	//创建玩家简单移动控制器
	SimpleMoveController* simple_move_controller = SimpleMoveController::create();

	//设置移动速度
	simple_move_controller->set_ixspeed(0);
	simple_move_controller->set_iyspeed(0);

	//将控制器添加到场景中让Upadate被调用
	this->addChild(simple_move_controller);

	//设置控制器到主角身上
	mplayer->set_controller(simple_move_controller);

	this->addChild(mplayer,2);

	this->addChild(_tiledmap);

	//创建EventListener
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event) {
		//Vec2 pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		
		Vec2 pos = Director::getInstance()->convertToGL(touch->getLocationInView());

		//有点问题，暂时用不了：fire里的addChild()没能成功
		//mplayer->attack(this,pos);	

		auto offset = pos - mplayer->getPosition();
		offset.normalize();
		auto destination = offset * 2000;

		//子弹添加到枪口的位置，暂时设置为武器锚点的位置，后期改
		auto bullet = Sprite::create("Projectile.png");
		bullet->setScale(1.5);
		bullet->setPosition(Vec2(mplayer->getPositionX(), mplayer->getPositionY()));
		this->addChild(bullet);

		//创建子弹的动作
		auto bulletMove = MoveBy::create(2.0f, destination);
		auto actionRemove = RemoveSelf::create();

		//日志输出touch的坐标、武器初始坐标、子弹飞行方向
		log("Touch:x=%f, y=%f", pos.x, pos.y);
		log("Weapon:x=%f, y=%f", this->getPositionX(), this->getPositionY());
		log("mplayer:x=%f, y=%f", mplayer->getPositionX(), mplayer->getPositionY());
		log("m_sprite:x=%f, y=%f", mplayer->getSprite()->getPositionX(), mplayer->getSprite()->getPositionY());
		log("Direction:x=%f, y=%f", offset.x, offset.y);

		//发射子弹
		bullet->runAction(Sequence::create(bulletMove, actionRemove, nullptr));
	
		/*auto bullet = Sprite::create("Projectile.png");
		bullet->setScale(0.5);
		bullet->setPosition(Vec2(mplayer->getPositionX(), mplayer->getPositionY()));
		this->addChild(bullet);*/
		
		return true;
	};

	listener->onTouchMoved = [](Touch* touch, Event* event) {

	};

	listener->onTouchEnded = [](Touch* touch, Event*event) {

	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


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

