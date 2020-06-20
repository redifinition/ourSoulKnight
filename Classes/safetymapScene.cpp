#include "HelloWorldScene.h"
#include "MyHelloWorldScene.h"
#include "audio.h"
#include "safetymapScene.h"

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
	// åˆå§‹åŒ–Physics
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*play game music*/
	audio_home->stopBackgroundMusic();
	audio_game->playBackgroundMusic("game_music.mp3", true);

	std::string floor_layer_file = "myfirstmap2.tmx";//µØÍ¼ÎÄ¼þ

	_tiledmap = TMXTiledMap::create(floor_layer_file);
	_tiledmap->setAnchorPoint(Vec2::ZERO);
	_tiledmap->setPosition(Vec2::ZERO);

	log("map size:(%f, %f)", _tiledmap->getContentSize().width,_tiledmap->getContentSize().height);

	//æ·»åŠ playerå¹¶ç»‘å®šæ­¦å™?

	Sprite* player_sprite = Sprite::create("turn right 1.png");
	Knight* mplayer = Knight::create();
	ShotGun* initialWeapon = ShotGun::create("goblin_guard_shotgun.png");
	mplayer->bindSprite(player_sprite);
	mplayer->bindWeapon(initialWeapon);
	mplayer->setTiledMap(_tiledmap);

	
	TMXObjectGroup* objGroup = _tiledmap->getObjectGroup("objects");

	ValueMap player_point_map = objGroup->getObject("PlayerPoint");
	float playerX = player_point_map.at("x").asFloat();
	float playerY = player_point_map.at("y").asFloat();

	//è®¾ç½®çŽ©å®¶åæ ‡
	mplayer->setPosition(Point(playerX,playerY));

	//æ·»åŠ ä¸€ä¸ªæµ‹è¯•ç”¨çš„monster
	Sprite* monster_sprite = Sprite::create("LongRemoteSoldier.png");
	RemoteSoldier* monster = RemoteSoldier::create(LONGREMOTE,this);

	monster->bindSprite(monster_sprite);
	//monster->setTiledMap(_tiledmap);

	TMXObjectGroup* bulletGroup = _tiledmap->getObjectGroup("bullet");

	ValueMap monster_point_map = bulletGroup->getObject("bullet1");
	float monsterX = monster_point_map.at("x").asFloat();
	float monsterY = monster_point_map.at("y").asFloat();
	monster->setPosition(Point(monsterX, monsterY));
	
	//åˆ›å»ºæ€ªç‰©
	RemoteSoldierManager* remoteSoldierManager = RemoteSoldierManager::create(this, mplayer, _tiledmap);
	this->m_remoteSoldierManager = remoteSoldierManager;
	_tiledmap->addChild(remoteSoldierManager, 4);

	//åˆ›å»ºçŽ©å®¶ç®€å•ç§»åŠ¨æŽ§åˆ¶å™¨
	SimpleMoveController* simple_move_controller = SimpleMoveController::create();

	//è®¾ç½®ç§»åŠ¨é€Ÿåº¦
	simple_move_controller->set_ixspeed(0);
	simple_move_controller->set_iyspeed(0);

	//å°†æŽ§åˆ¶å™¨æ·»åŠ åˆ°åœºæ™¯ä¸­è®©Upadateè¢«è°ƒç”?
	this->addChild(simple_move_controller);

	//è®¾ç½®æŽ§åˆ¶å™¨åˆ°ä¸»è§’èº«ä¸Š
	mplayer->set_controller(simple_move_controller);
	simple_move_controller->bind_sprite(player_sprite);//Bind player
  
	//è®¾ç½®ç¢°æ’žæŽ©ç 
	this->m_player = mplayer;
	this->m_monster = monster;

	m_monster->getPhysicsBody()->setCategoryBitmask(0x02);
	m_monster->getPhysicsBody()->setContactTestBitmask(0x04);
	

	this->addChild(_tiledmap);

	_tiledmap->addChild(mplayer,2);
	_tiledmap->addChild(monster, 2);
	
	//this->addChild(monster,2);
	//this->addChild(mplayer,2);
	log("player pos0:(%f, %f)", playerX, playerY);
	log("monster pos0:(%f, %f)", monsterX, monsterY);

	
	//åˆ›å»ºEventListener
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(safetymap::onTouchBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	
	//åˆ›å»ºcontactListener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(safetymap::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

bool safetymap::onTouchBegin(Touch* touch, Event* event) {
	/*if(!m_player->getLockedTarget()->getalreadyDead())){
		Vec2 pos = m_player->getLockedTarget()->getPosition();
		m_player->rotateWeapon(pos);
		m_player->attack(this, pos);
	}
	else{
		//ÕÒÒ»¸ö¾àÀë×î½üµÄsoldier¹¥»÷
		for (auto target : this->m_remoteSoldierManager->getSoldierArr()){
			if (target->getalreadyDead()){
				continue;
			}
			Vec2 direction = target->getPosition() - m_player->getPosition();
			float distance = sqrt(direction.x*direction.x + direction.y*direction.y);

			/*if(!target->getalreadyDead())
			{
				Vec2 pos = target->getPosition();
				m_player->rotateWeapon(pos);
				m_player->attack(this,pos);
			}
			else {
				m_player->resetWeaponPos();
				m_player->attack(this, Vec2(m_player->getPositionX() + 1, m_player->getPositionY()));
			}
		}
	}*/
	m_player->resetWeaponPos();
	m_player->attack(this, Vec2(m_player->getPositionX() + 1, m_player->getPositionY()));
	return true;
}

bool safetymap::onContactBegin(PhysicsContact& contact) {

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() > 0)
		{
			if (nodeB->getTag() == -1)
			{
				this->m_player->takeDamage(nodeA->getTag());
			}
			else if (nodeB->getTag() == -2)
			{
				//this->m_monster->takeDamage(nodeA->getTag());
				//ÕÒ³öÊÇÄÄ¸ö¹ÖÎïºÍ×Óµ¯·¢ÉúÁËÅö×²
				for (auto Soldier : this->m_remoteSoldierManager->getSoldierArr())
				{
					if (nodeB->getMonsterID() == Soldier->getMonsterID())
					{
						Soldier->takeDamage(nodeA->getTag());
					}
				}
			}
			nodeA->removeFromParentAndCleanup(true);
		}

		//ºÍÉÏÃæµÄ´úÂë¿éÊÇ¾µÏñµÄ£¬ÒòÎªnodeAºÍnodeB²»ÖªµÀÄÄÒ»¸öÊÇ×Óµ¯
		else if (nodeB->getTag() > 0)
		{
			if (nodeA->getTag() == -1)
			{
				this->m_player->takeDamage(nodeB->getTag());
			}
			else if (nodeA->getTag() == -2)
			{
				//this->m_monster->takeDamage(nodeB->getTag());
				for (auto Soldier : this->m_remoteSoldierManager->getSoldierArr())
				{
					if (nodeA->getMonsterID() == Soldier->getMonsterID())
					{
						Soldier->takeDamage(nodeB->getTag());
					}
				}
			}
			nodeB->removeFromParentAndCleanup(true);
		}
	}
		return true;
}

/*void safetymap::add_player(TMXTiledMap* map)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½ï¿½ï¿½
	Sprite* player_sprite = Sprite::create("player.png");
	Player* mplayer = Player::create();
	mplayer->bind_sprite(player_sprite);
	mplayer->run();

    //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	mplayer->setPosition(Vec2(100, visibleSize.height / 2));

	_tiledmap->addChild(mplayer);
}*/



