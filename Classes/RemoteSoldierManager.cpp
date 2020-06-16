#include "RemoteSoldierManager.h"

RemoteSoldierManager* RemoteSoldierManager::create(Scene* currentScene, Entity* player, TMXTiledMap* map)
{
	RemoteSoldierManager* remoteSoldierManager = new RemoteSoldierManager;
	if (remoteSoldierManager && remoteSoldierManager->init(currentScene, player, map))
	{
		remoteSoldierManager->autorelease();
		return remoteSoldierManager;
	}
	CC_SAFE_DELETE(remoteSoldierManager);
	return nullptr;
}
bool RemoteSoldierManager::init(Scene* currentScene, Entity* player, TMXTiledMap* map)
{
	createMonsters();
	_currentScene = currentScene;
	_player = player;
	_map = map;
	this->scheduleUpdate();
	this->schedule(CC_SCHEDULE_SELECTOR(RemoteSoldierManager::attackUpdate), 2.0f);
	return true;
}

void RemoteSoldierManager::createMonsters()
{
	RemoteSoldier* remoteSoldier = nullptr;
	Sprite* sprite = nullptr;

	for (int i = 0; i < MAX_REMOTE_SOLDIER_NUM; i++)
	{
		srand((unsigned)time(nullptr));
		int random = rand() % 2;
		if (random == 0) 
		{
			remoteSoldier = RemoteSoldier::create(LONGREMOTE, _currentScene);
			remoteSoldier->bindSprite(Sprite::create("LongRemoteSoldier.png"));
		}
		else
		{
			remoteSoldier = RemoteSoldier::create(SHORTREMOTE, _currentScene);
			remoteSoldier->bindSprite(Sprite::create("ShortRemoteSoldier.png"));
		}
		remoteSoldier->setPosition(this->setSoldierPosition(i));
		m_remoteSoldierArr.pushBack(remoteSoldier);
	}
}

void RemoteSoldierManager::update(float dt)
{
	for (auto remoteSoldier : m_remoteSoldierArr)
	{
		if(!(remoteSoldier->getalreadyDead()))
		{
			srand((unsigned)time(nullptr));
			int random = rand() % 4;
			//todo:关于地图边界的问题
			if (random == 0) //up
			{
				remoteSoldier->setPositionY(remoteSoldier->getPositionY + 4);
			}
			else if (random == 1) //down
			{
				remoteSoldier->setPositionY(remoteSoldier->getPositionY - 4);
			}
			else if (random == 1) //left
			{
				remoteSoldier->setPositionX(remoteSoldier->getPositionX - 4);
			}
			else //right
			{
				remoteSoldier->setPositionX(remoteSoldier->getPositionX + 4);
			}
		}
	}
}

void RemoteSoldierManager::attackUpdate(float dt)
{
	for (auto remoteSoldier : m_remoteSoldierArr)
	{
		if (!(remoteSoldier->getalreadyDead()))
		{
			double difX = remoteSoldier->getPositionX() - _player->getPositionX();
			double difY = remoteSoldier->getPositionY() - _player->getPositionY();
			if(difX * difX + difY * difY <= LONG_REMOTE_SOLDIER_ATTACK_RADIUS* LONG_REMOTE_SOLDIER_ATTACK_RADIUS)
				remoteSoldier->attack(_player);
		}
	}
}

Vec2 RemoteSoldierManager::setSoldierPosition(int num)
{
	TMXObjectGroup* objGroup = _map->getObjectGroup("bullet");
	float remoteSoldierX, remoteSoldierY;
	if (num == 0) 
	{
		ValueMap remoteSoldierMap = objGroup->getObject("remote_bullet1");
		remoteSoldierX = remoteSoldierMap.at("x").asFloat();
		remoteSoldierY = remoteSoldierMap.at("y").asFloat();
	}
	else if (num == 1)
	{
		ValueMap remoteSoldierMap = objGroup->getObject("remote_bullet2");
		remoteSoldierX = remoteSoldierMap.at("x").asFloat();
		remoteSoldierY = remoteSoldierMap.at("y").asFloat();
	}
	else if(num == 2)
	{
		ValueMap remoteSoldierMap = objGroup->getObject("remote_bullet3");
		remoteSoldierX = remoteSoldierMap.at("x").asFloat();
		remoteSoldierY = remoteSoldierMap.at("y").asFloat();
	}
	else if (num == 3)
	{
		ValueMap remoteSoldierMap = objGroup->getObject("remote_bullet4");
		remoteSoldierX = remoteSoldierMap.at("x").asFloat();
		remoteSoldierY = remoteSoldierMap.at("y").asFloat();
	}
	else
	{
		ValueMap remoteSoldierMap = objGroup->getObject("remote_bullet5");
		remoteSoldierX = remoteSoldierMap.at("x").asFloat();
		remoteSoldierX = remoteSoldierMap.at("y").asFloat();
	}
	return Vec2(remoteSoldierX, remoteSoldierX);
}