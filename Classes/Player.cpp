#include "Player.h"
#include "safetymapScene.h"
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

	//��ͼ������
	Size mapTiledNum = m_map->getMapSize();

	//��ͼ������Ӵ��?
	Size tiledSize = m_map->getTileSize();

	//��ͼ��С
	Size mapSize = Size(mapTiledNum.width*tiledSize.width, mapTiledNum.height*tiledSize.height);

	//��Ļ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//������
	Point spritePos = getPosition();

	float x = std::max(spritePos.x,visibleSize.width/2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	//��������곬��Χ����ȡ������?
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	//Ŀ���?
	Point desPos = Point(x, y);

	//��Ļ�е�
	Point centPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	Point viewPos = centPos - desPos;

	parent->setPosition(viewPos);

}

void Player::set_tag_position(int x, int y)
{
	/*�ж�ǰ���Ƿ񲻿�ͨ��*/
	Size spriteSize = m_sprite->getContentSize();
	Point dstPos = Point(x+spriteSize.width/2, y);
	Point dstPos_y = Point(x + spriteSize.width / 2, y - spriteSize.height / 2);
	//�����ΪPlayer��Ӧ���ƫ�µ�λ�ã�Ϊ���ж�Player�·��Ľ�����

	/*������ǰ����ͼ����λ��*/
	Point tiledPos = tileCoordForPosition(Point(dstPos.x, dstPos.y));
	Point tiledPos_right = tileCoordForPosition(Point(dstPos.x + spriteSize.width / 2, dstPos.y));
	Point tiledPos_bottom = tileCoordForPosition(Point(dstPos.x, dstPos.y- spriteSize.height / 2));
	//�Ըþ������ڸ��ӵ�ǰ���жϣ�
	/*��õ�ͼ���ӵ�Ψһ���*/
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
	int x, y;
    x = (pos.x*1.8) / tiledSize.width;

    /*y������Ҫת��һ�£���Ϊ����ϵ��tiled��ͬ*/
	y = (mapTiledNum.height*tiledSize.height - pos.y*1.8) / tiledSize.height;
	
	if (x > 0)
		x--;
	if (y > 0)
		y-=0;

	return Point(x, y);
}
