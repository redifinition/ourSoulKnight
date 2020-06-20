#include "Player.h"
#include "safetymapScene.h"

Player::Player()
{
	_HP = 5;
	_MP = 100;
	_AC = 5;
	_alreadyDead = false;
}

Player::~Player() {

}
bool Player::init()
{
	return true;
}

bool Player::bindSprite(Sprite*sprite) {
	this->m_sprite = sprite;
	if (m_sprite == nullptr)
	{
		printf("m_sprite in this entity is nullptr, check wether the file used to create the sprite in right dictionary.");
		return false;
	}
	else
	{
		this->addChild(m_sprite);
		Size size = m_sprite->getContentSize();
		m_sprite->setPosition(Point(size.width*0.5f, size.height*0.5f));
		this->setContentSize(size);
		this->setAnchorPoint(Vec2(0.5, 0.5));

		//娣诲姞鐗╃悊纰版挒妯″瀷
		auto physicsBody = PhysicsBody::createBox(size, PhysicsMaterial(0.0f, 0.0f, 0.0f));
		physicsBody->setDynamic(false);
		physicsBody->setCategoryBitmask(0x01);
		physicsBody->setContactTestBitmask(0x04);
		this->addComponent(physicsBody);

		return true;
	}
}
//鍜岃鑹叉鍣ㄧ浉鍏崇殑鍑芥暟
bool Player::bindWeapon(Weapon* weapon) {
	if (weapon == nullptr)
	{
		printf("m_weapon in this player is nullptr, check wether the file used to create the weapon in right dictionary.");
		return false;
	}
	else
	{
		this->m_weaponArr.pushBack(weapon);
		this->m_weapon = weapon;	//褰撳墠姝﹀櫒灏辫缃负缁戝畾鐨勬鍣?
		if (m_weapon == nullptr)
		{
			log("m_weapon is nullptr");
		}

		//璁惧畾姝﹀櫒浣嶇疆
		Size size = m_sprite->getContentSize();
		m_weapon->setPosition(Vec2(size.width*getWpPos().x, size.height*getWpPos().y));//*getWpPos().x
			//鐢ㄤ簬鍒濇娴嬭瘯锛屼箣鍚庡垹闄わ紝涓嶅悓姝﹀櫒鐨勭缉鏀句笉鍚岋紝瑕佷箞鎶婄缉鏀炬斁鍦ㄥ垱寤哄嚱鏁伴噷闈紝瑕佷箞灏辨妸姝﹀櫒鍥剧墖鐨勫ぇ灏忚皟瀵?

		this->addChild(m_weapon);

		_attack = m_weapon->getAttack();
		return true;
	}
}

void Player::attack(Scene* currentScene,const Vec2& pos) {
	if (_MP - m_weapon->getMpConsume() >= 0) {
		_MP -= m_weapon->getMpConsume();
		this->m_weapon->fire(currentScene, pos, this);
		log("player pos:(%f,%f)", this->getPositionX(), this->getPositionY());
	}
}

void Player::rotateWeapon(const Vec2& pos) {
	auto direction = pos - this->getPosition();
	float x = direction.x;
	float y = direction.y;
	if (x > 0 && y > 0) {
		this->m_weapon->setRotation(-45.0f);
	}
	else if (x > 0 && y < 0) {
		this->m_weapon->setRotation(+45.0f);
	}
}

void Player::resetWeaponPos() {
	this->m_weapon->setRotation(0.0f);
}

void Player::switchWeapon() {

}

void Player::skill() {

}

void Player::takeDamage(int damage)
{
	if (_AC > 0)
	{
		_AC -= damage;
	}
	else 
	{
		_HP -= damage;
		if (_HP <= 0)
		{
			_alreadyDead = true;
			this->die();
		}
	}
}

void Player::die()
{

	this->setVisible(false);
	
}

//鍜岄敭鐩樻帶鍒剁浉鍏崇殑鍑芥暟
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

	int x, y;
    x = (pos.x*1.8) / tiledSize.width;

    /*y鍧愭爣闇�瑕佽浆鎹竴涓嬶紝鍥犱负鍧愭爣绯诲拰tiled涓嶅悓*/
	y = (mapTiledNum.height*tiledSize.height - pos.y*1.8) / tiledSize.height;

	/*格子从零开始*/
	if (x > 0)
		x--;
	if (y > 0)
		y-=0;

	return Point(x, y);
}


