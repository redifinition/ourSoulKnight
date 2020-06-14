#include "Player.h"

Player::Player()
{
	_HP = 5;
	_MP = 100;
	_AC = 5;
	_weaponPosition = Vec2(0.8, 0.3);

}

Player::~Player() {

}
bool Player::init()
{
	return true;
}

//和角色武器相关的函数
bool Player::bindWeapon(Weapon* weapon) {
	if (weapon == nullptr)
	{
		printf("m_weapon in this player is nullptr, check wether the file used to create the weapon in right dictionary.");
		return false;
	}
	else
	{
		this->m_weaponArr.pushBack(weapon);
		this->m_weapon = weapon;	//当前武器就设置为绑定的武器
		if (m_weapon == nullptr)
		{
			log("m_weapon is nullptr");
		}

		
		//设定武器位置
		Size size = m_sprite->getContentSize();
;		m_weapon->setPosition(Point(size.width*getWpPos().x,size.height*getWpPos().y));
		m_weapon->setScale(0.06);	//用于初次测试，之后删除，不同武器的缩放不同，要么把缩放放在创建函数里面，要么就把武器图片的大小调对

		this->addChild(m_weapon);

		return true;
	}
}

void Player::switchWeapon() {

}

void Player::skill() {

}

void Player::attack(Scene* currentScene,const Vec2& pos) {
	auto offset = pos - this->getPosition();
	offset.normalize();
	auto destination = offset * 2000;

	//子弹添加到枪口的位置，暂时设置为武器锚点的位置，后期改
	auto bullet = Sprite::create("Projectile.png");
	bullet->setScale(1.5);
	bullet->setPosition(Vec2(this->getPositionX(), this->getPositionY()));
	currentScene->addChild(bullet);

	//创建子弹的动作
	auto bulletMove = MoveBy::create(2.0f, destination);
	auto actionRemove = RemoveSelf::create();

	//日志输出touch的坐标、武器初始坐标、子弹飞行方向
	log("Destination:x=%f, y=%f", pos.x, pos.y);
	log("mplayer:x=%f, y=%f", this->getPositionX(), this->getPositionY());
	log("m_sprite:x=%f, y=%f", this->getSprite()->getPositionX(), this->getSprite()->getPositionY());
	log("Direction:x=%f, y=%f", offset.x, offset.y);

	//发射子弹
	bullet->runAction(Sequence::create(bulletMove, actionRemove, nullptr));
}

//和键盘控制相关的函数
void Player::setViewPointByPlayer()
{
	if (m_sprite == NULL)
		return;
	Layer* parent = (Layer*)getParent();


	Size mapTiledNum = m_map->getMapSize();


	Size tiledSize = m_map->getTileSize();


	Size mapSize = Size(mapTiledNum.width*tiledSize.width, mapTiledNum.height*tiledSize.height);


	auto visibleSize = Director::getInstance()->getVisibleSize();


	Point spritePos = getPosition();

	float x = std::max(spritePos.x,visibleSize.width/2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	
	Point desPos = Point(x, y);

	
	Point centPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	Point viewPos = centPos - desPos;

	parent->setPosition(viewPos);

}

void Player::set_tag_position(int x, int y)
{

	Size spriteSize = m_sprite->getContentSize();
	Point dstPos = Point(x+spriteSize.width/2, y);
	Point dstPos_y = Point(x + spriteSize.width / 2, y - spriteSize.height / 2);

	Point tiledPos = tileCoordForPosition(Point(dstPos.x, dstPos.y));
	Point tiledPos_right = tileCoordForPosition(Point(dstPos.x + spriteSize.width / 2, dstPos.y));
	Point tiledPos_bottom = tileCoordForPosition(Point(dstPos.x, dstPos.y- spriteSize.height / 2));

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

	int y = (2560-pos.y*1.8) / tiledSize.height;

	if (x > 0)
		x--;
	if (y > 0)
		y-=0;

	return Point(x, y);
}