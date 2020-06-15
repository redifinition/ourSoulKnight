#include "HelloWorldScene.h"
#include "MyHelloWorldScene.h"
#include "audio.h"
#include "safetymapScene.h"
#include "SimpleMoveController.h"
#include "Controller.h"
#include "Player.h"
#include "Knight.h"
#include "Gun.h"

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
	// 初始化Physics
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//创建地图背景
	std::string floor_layer_file = "myfirstmap3.tmx";//地图文件
	_tiledmap = TMXTiledMap::create(floor_layer_file);
	_tiledmap->setAnchorPoint(Vec2::ZERO);
	_tiledmap->setPosition(Vec2::ZERO);

	//添加player并绑定武器
	Sprite* player_sprite = Sprite::create("turn right 1.png");
	Knight* mplayer = Knight::create();
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

	//添加一个测试用的monster
	Sprite* monster_sprite = Sprite::create("turn right 2.png");
	Player* monster = Player::create();
	monster->bindSprite(monster_sprite);
	monster->setTiledMap(_tiledmap);

	TMXObjectGroup* bulletGroup = _tiledmap->getObjectGroup("bullet");

	ValueMap monster_point_map = bulletGroup->getObject("bullet1");
	float monsterX = monster_point_map.at("x").asFloat();
	float monsterY = monster_point_map.at("y").asFloat();
	monster->setPosition(Point(monsterX, monsterY));
	
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

	//设置碰撞掩码
	this->m_player = mplayer;
	this->m_monster = monster;

	m_monster->getPhysicsBody()->setCategoryBitmask(0x02);
	m_monster->getPhysicsBody()->setContactTestBitmask(0x04);

	this->addChild(monster,2);
	this->addChild(mplayer,2);

	this->addChild(_tiledmap);

	//创建EventListener
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(safetymap::onTouchBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//创建contactListener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(safetymap::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

bool safetymap::onTouchBegin(Touch* touch, Event* event) {
	Vec2 pos = m_monster->getPosition();
	m_player->rotateWeapon(pos);
	m_player->attack(this, pos);
	return true;
}

bool safetymap::onContactBegin(PhysicsContact& contact) {

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == 10)
		{
			nodeA->removeFromParentAndCleanup(true);
		}
		else if (nodeB->getTag() == 10)
		{
			nodeB->removeFromParentAndCleanup(true);
		}

	}

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

