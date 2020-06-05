#include "Player.h"

bool Player::init()
{
	isJumping = false;
	return true;
}


void Player::run()
{

}

void Player::setViewPointByPlayer()
{
	if (m_sprite == NULL)
		return;
	Layer* parent = (Layer*)getParent();

	//地图方块数
	Size mapTiledNum = m_map->getMapSize();

	//地图单个格子大小
	Size tiledSize = m_map->getTileSize();

	//地图大小
	Size mapSize = Size(mapTiledNum.width*tiledSize.width, mapTiledNum.height*tiledSize.height);

	//屏幕大小
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//主角坐标
	Point spritePos = getPosition();

	float x = std::max(spritePos.x,visibleSize.width/2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	//如果主角坐标超出范围，则取主角坐标
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	//目标点
	Point desPos = Point(x, y);

	//屏幕中点
	Point centPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	Point viewPos = centPos - desPos;

	parent->setPosition(viewPos);

}

void Player::set_tag_position(int x, int y)
{
	/*判断前面是否不可通行*/
	Size spriteSize = m_sprite->getContentSize();
	Point dstPos = Point(x+spriteSize.width/2, y);
	Point dstPos_y = Point(x + spriteSize.width / 2, y - spriteSize.height / 2);
	//该坐标为Player对应坐标偏下的位置，为了判断Player下方的建筑物

	/*获得主角前方地图格子位置*/
	Point tiledPos = tileCoordForPosition(Point(dstPos.x, dstPos.y));
	Point tiledPos_right = tileCoordForPosition(Point(dstPos.x + spriteSize.width / 2, dstPos.y));
	Point tiledPos_bottom = tileCoordForPosition(Point(dstPos.x, dstPos.y- spriteSize.height / 2));
	//对该精灵所在格子的前方判断；
	/*获得地图格子的唯一标识*/
	int tileGid = meta->getTileGIDAt(tiledPos);
	int tiledGid_right = meta->getTileGIDAt(tiledPos_right); 
	int tiledGid_bottom = meta->getTileGIDAt(tiledPos_bottom);
	//int tileGid = meta->getTileGIDAt(Point(16,12));
	if (tileGid != 0)
	{
		Value properties = m_map->getPropertiesForGID(tileGid);

		Value proper = properties.asValueMap().at("Collidable");

		if (proper.asString().compare("true") == 0)
		{
			return;
		}
	}
	if(tiledGid_right != 0)
	{
		Value properties = m_map->getPropertiesForGID(tiledGid_right);

		Value proper = properties.asValueMap().at("Collidable");

		if (proper.asString().compare("true") == 0)
			return;
	}
	if (tiledGid_bottom != 0)
	{
		Value properties = m_map->getPropertiesForGID(tiledGid_bottom);

		Value proper = properties.asValueMap().at("Collidable");

		if (proper.asString().compare("true") == 0)
			return;
	}
	Entity::set_tag_position(x, y);

	setViewPointByPlayer();
}

void Player::setTiledMap(TMXTiledMap* map)
{
	this->m_map = map;

	this->meta = m_map->getLayer("meta");
	this->meta->setVisible(false);
}

Point Player::tileCoordForPosition(Point pos) {
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();

	int x = (pos.x*1.8)/ tiledSize.width;

     /*y坐标需要转换一下，因为坐标系和tiled不同*/
	int y = (2560-pos.y*1.8) / tiledSize.height;

	/*格子从零开始*/
	if (x > 0)
		x--;
	if (y > 0)
		y-=0;

	return Point(x, y);
}