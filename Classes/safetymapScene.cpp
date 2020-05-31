#include "HelloWorldScene.h"
#include "MyHelloWorldScene.h"
#include "audio.h"
#include "safetymapScene.h"
#include "SimpleMoveController.h"
#include "Controller.h"
#include "ControllerListener.h"

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
	//������ͼ����

	std::string floor_layer_file = "myfirstmap.tmx";//�ذ��ļ�
	_tiledmap = TMXTiledMap::create(floor_layer_file);
	//_tiledmap->setScale(0.2);




	//���player
	//auto pinfo = AutoPolygon::generatePolygon("player.png");
	Sprite* player_sprite = Sprite::create("turn right 1.png");
	Player* mplayer = Player::create();
	mplayer->bind_sprite(player_sprite);

	mplayer->run();


	mplayer->setScale(0.1);
	TMXObjectGroup* objGroup = _tiledmap->getObjectGroup("knight");//���ض����
	//��������������
	ValueMap player_point_map = objGroup->getObject("PlayerPoint");
	float playerX = player_point_map.at("x").asFloat();
	float playerY = player_point_map.at("y").asFloat();

	//�����������
	mplayer->setPosition(Vec2(visibleSize.width/2-100, visibleSize.height/2));


	auto knight_animation = Animation::create();
	char nameSize[30] = { 0 };
	for (int i = 1; i <= 4; i++)
	{
		sprintf(nameSize, "turn right %d.png", i);
		knight_animation->addSpriteFrameWithFile(nameSize);
	}
	knight_animation->setDelayPerUnit(0.08f);//���ö���֡ʱ����
	knight_animation->setLoops(-1);
	knight_animation->setRestoreOriginalFrame(true);
	Animate* animate_knight = Animate::create(knight_animation);
	player_sprite->runAction(animate_knight);

	//������Ҽ��ƶ�������
	SimpleMoveController* simple_move_controller = SimpleMoveController::create();

	//�����ƶ��ٶ�
	simple_move_controller->set_speed(1);

	//����������ӵ���������Upadate������
	this->addChild(simple_move_controller);
	//���ÿ���������������
	mplayer->set_controller(simple_move_controller);

	this->addChild(mplayer,1);

	this->addChild(_tiledmap, -1);




	return true;
}

/*void safetymap::add_player(TMXTiledMap* map)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//����һ������
	Sprite* player_sprite = Sprite::create("player.png");
	Player* mplayer = Player::create();
	mplayer->bind_sprite(player_sprite);
	mplayer->run();

    //�����������
	mplayer->setPosition(Vec2(100, visibleSize.height / 2));

	_tiledmap->addChild(mplayer);
}*/
