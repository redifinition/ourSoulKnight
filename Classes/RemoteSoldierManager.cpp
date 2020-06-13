#include "RemoteSoldierManager.h"

RemoteSoldierManager* RemoteSoldierManager::create(Scene* currentScene)
{
	RemoteSoldierManager* remoteSoldierManager = new RemoteSoldierManager;
	if (remoteSoldierManager && remoteSoldierManager->init(currentScene))
	{
		remoteSoldierManager->autorelease();
		return remoteSoldierManager;
	}
	CC_SAFE_DELETE(remoteSoldierManager);
	return nullptr;
}
bool RemoteSoldierManager::init(Scene* currentScene)
{
	createMonsters();
	_currentScene = currentScene;
	this->scheduleUpdate();
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
		//remoteSoldier->setset() 初始化坐标
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