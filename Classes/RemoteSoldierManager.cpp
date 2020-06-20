#include "RemoteSoldierManager.h"
#include "cocos2d.h"
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
	_currentScene = currentScene;
	_player = player;
	_map = map;
	createMonsters();
	this->scheduleUpdate();
	this->schedule(CC_SCHEDULE_SELECTOR(RemoteSoldierManager::attackUpdate), 2.0f);
	meta = _map->getLayer("meta");

	return true;
}

void RemoteSoldierManager::createMonsters()
{
	RemoteSoldier* remoteSoldier = nullptr;
	Sprite* sprite = nullptr;
	srand((unsigned)time(nullptr));
	for (int i = 0; i < MAX_REMOTE_SOLDIER_NUM; i++)
	{
		int random = rand() % 2;
		log("random:%d", random);
		if (random == 0) 
		{
			remoteSoldier = RemoteSoldier::create(LONGREMOTE, _currentScene);
			sprite = Sprite::create("LongRemoteSoldier.png");
			remoteSoldier->bindSprite(sprite);
		}
		else
		{
			remoteSoldier = RemoteSoldier::create(SHORTREMOTE, _currentScene);
			sprite = Sprite::create("LongRemoteSoldier.png");
			remoteSoldier->bindSprite(sprite);
		}
		remoteSoldier->setPosition(this->setSoldierPosition(i));
		_map->addChild(remoteSoldier,10);
		m_remoteSoldierArr.pushBack(remoteSoldier);
	}
}

void RemoteSoldierManager::update(float dt)
{
	for (auto remoteSoldier : m_remoteSoldierArr)
	{
		if (!(remoteSoldier->getalreadyDead()))
		{
			//remoteSoldier->setPosition(getRandomPosition(remoteSoldier->getPosition()));
			int random = rand()%4;
			//log("random:%d", random);
			//todo:¹ØÓÚµØÍ¼±ß½çµÄÎÊÌâ
			if (random == 0) //up
			{
				float bullet_x = remoteSoldier->getPositionX();
				float bullet_y = remoteSoldier->getPositionY() + 4;
				Point tiledPos = tileCoordForPosition(Point(bullet_x,bullet_y));
				int tileGid = meta->getTileGIDAt(tiledPos);

				//int tileGid = meta->getTileGIDAt(Point(16,12));
				if (tileGid != 0)
				{
					Value properties = _map->getPropertiesForGID(tileGid);

					Value proper = properties.asValueMap().at("Collidable");

					if (proper.asString().compare("true") == 0)
					{
						remoteSoldier->setPosition(remoteSoldier->getPosition());
					}
				}
				if (bullet_x >= 1422 || bullet_y+4 >= 1422 || bullet_x < 0 || bullet_y+4 < 0)
				{
					remoteSoldier->setPosition(remoteSoldier->getPosition());
				}
				remoteSoldier->setPosition(Point(bullet_x,bullet_y));
			}
			else if (random == 1) //down
			{
				float bullet_x = remoteSoldier->getPositionX();
				float bullet_y = remoteSoldier->getPositionY() - 4;
				Point tiledPos = tileCoordForPosition(Point(bullet_x, bullet_y));
				int tileGid = meta->getTileGIDAt(tiledPos);

				//int tileGid = meta->getTileGIDAt(Point(16,12));
				if (tileGid != 0)
				{
					Value properties = _map->getPropertiesForGID(tileGid);

					Value proper = properties.asValueMap().at("Collidable");

					if (proper.asString().compare("true") == 0)
					{
						remoteSoldier->setPosition(remoteSoldier->getPosition());
					}
				}
				if (bullet_x >= 1422 || bullet_y - 4 >= 1422 || bullet_x < 0 || bullet_y - 4 < 0)
				{
					remoteSoldier->setPosition(remoteSoldier->getPosition());
				}
				remoteSoldier->setPosition(Point(bullet_x, bullet_y));
			}
			else if (random == 2) //left
			{
				float bullet_x = remoteSoldier->getPositionX()-4;
				float bullet_y = remoteSoldier->getPositionY();
				Point tiledPos = tileCoordForPosition(Point(bullet_x, bullet_y));
				int tileGid = meta->getTileGIDAt(tiledPos);

				//int tileGid = meta->getTileGIDAt(Point(16,12));
				if (tileGid != 0)
				{
					Value properties = _map->getPropertiesForGID(tileGid);

					Value proper = properties.asValueMap().at("Collidable");

					if (proper.asString().compare("true") == 0)
					{
						remoteSoldier->setPosition(remoteSoldier->getPosition());
					}
				}
				if (bullet_x -4>= 1422 || bullet_y  >= 1422 || bullet_x-4 < 0 || bullet_y < 0)
				{
					remoteSoldier->setPosition(remoteSoldier->getPosition());
				}
				remoteSoldier->setPosition(Point(bullet_x, bullet_y));
			}
			else //right
			{
				float bullet_x = remoteSoldier->getPositionX()+4;
				float bullet_y = remoteSoldier->getPositionY();
				Point tiledPos = tileCoordForPosition(Point(bullet_x, bullet_y));
				int tileGid = meta->getTileGIDAt(tiledPos);

				//int tileGid = meta->getTileGIDAt(Point(16,12));
				if (tileGid != 0)
				{
					Value properties = _map->getPropertiesForGID(tileGid);

					Value proper = properties.asValueMap().at("Collidable");

					if (proper.asString().compare("true") == 0)
					{
						remoteSoldier->setPosition(remoteSoldier->getPosition());
					}
				}
				if (bullet_x +4>= 1422 || bullet_y >= 1422 || bullet_x+4 < 0 || bullet_y < 0)
				{
					remoteSoldier->setPosition(remoteSoldier->getPosition());
				}
				remoteSoldier->setPosition(Point(bullet_x, bullet_y));
			}
			//log("remoteSoldier:x=%f, y=%f", remoteSoldier->getPositionX(), remoteSoldier->getPositionY());
		}
	}
	
}

void RemoteSoldierManager::attackUpdate(float dt)
{
	for (auto remoteSoldier : m_remoteSoldierArr)
	{
		if (!(remoteSoldier->getalreadyDead()))
		{
			float difX = remoteSoldier->getPositionX() - _player->getPositionX();
			float difY = remoteSoldier->getPositionY() - _player->getPositionY();
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
		//log("startremoteSoldier:x=%f, y=%f", remoteSoldierX, remoteSoldierY);
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
		remoteSoldierY = remoteSoldierMap.at("y").asFloat();
	}
	return Vec2(remoteSoldierX, remoteSoldierY);
}

Point RemoteSoldierManager::tileCoordForPosition(Point pos)
{
	Size mapTiledNum = _map->getMapSize();
	Size tiledSize = _map->getTileSize();

	int x, y;
	x = (pos.x*1.8) / tiledSize.width;

	/*y鍧愭爣闇€瑕佽浆鎹竴涓嬶紝鍥犱负鍧愭爣绯诲拰tiled涓嶅悓*/
	y = (mapTiledNum.height*tiledSize.height - pos.y*1.8) / tiledSize.height;

	/*格子从零开始*/
	if (x > 0)
		x--;
	if (y > 0)
		y -= 0;
	return Point(x, y);
}

Point RemoteSoldierManager::getRandomPosition(Point pos)
{
	int random = rand() % 4;
	//log("random:%d", random);
	//todo:关于地图边界的问题
	if (random == 0) //up
	{

		pos.y += 4;
	}
	else if (random == 1) //down
	{
		pos.y -= 4;
	}
	else if (random == 2) //left
	{
		pos.x -= 4;
	}
	else //right
	{
		pos.x += 4;
	}
	//log("remoteSoldier:x=%f, y=%f", remoteSoldier->getPositionX(), remoteSoldier->getPositionY());


	Point tiledPos = tileCoordForPosition(pos);
	int tileGid = meta->getTileGIDAt(tiledPos);

	//int tileGid = meta->getTileGIDAt(Point(16,12));
	if (tileGid != 0)
	{
		Value properties = _map->getPropertiesForGID(tileGid);

		Value proper = properties.asValueMap().at("Collidable");

		if (proper.asString().compare("true") == 0)
		{
			return getRandomPosition(pos);
		}
	}
	if (pos.x >= 1422 || pos.y >= 1422||pos.x<0||pos.y<0)
	{
		return getRandomPosition(pos);
	}
	return pos;
}
