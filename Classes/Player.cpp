#include "Player.h"
#include "safetymapScene.h"

Player::Player()
{
	isJumping = false;
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
<<<<<<< HEAD

		//è®¾ç½®Playerçš„å¤§å°å’Œm_spriteçš„å¤§å°ä¸€è‡´ï¼Œå¦åˆ™ç¢°æ’žæ¨¡åž‹ä¼šä¸å¯¹
=======
		/*è®¾ç½®Playerçš„å¤§å°å’Œm_spriteçš„å¤§å°ä¸€è‡´ï¼Œå¦åˆ™ç¢°æ’žæ¨¡åž‹ä¼šä¸å¯?/
>>>>>>> bbd7442a8b0690efe4fd35c4788f1021c521395b
		Size size = m_sprite->getContentSize();
		m_sprite->setPosition(Point(size.width*0.5f, size.height*0.5f));
		this->setContentSize(size);
		this->setAnchorPoint(Vec2(0.5, 0.5));

		//æ·»åŠ ç‰©ç†ç¢°æ’žæ¨¡åž‹
		auto physicsBody = PhysicsBody::createBox(size, PhysicsMaterial(0.0f, 0.0f, 0.0f));
		physicsBody->setDynamic(false);
		physicsBody->setCategoryBitmask(0x01);
		physicsBody->setContactTestBitmask(0x04);
		this->addComponent(physicsBody);

		return true;
	}
}
//å’Œè§’è‰²æ­¦å™¨ç›¸å…³çš„å‡½æ•°
bool Player::bindWeapon(Weapon* weapon) {
	if (weapon == nullptr)
	{
		printf("m_weapon in this player is nullptr, check wether the file used to create the weapon in right dictionary.");
		return false;
	}
	else
	{
		this->m_weaponArr.pushBack(weapon);
		this->m_weapon = weapon;	//å½“å‰æ­¦å™¨å°±è®¾ç½®ä¸ºç»‘å®šçš„æ­¦å™?
		if (m_weapon == nullptr)
		{
			log("m_weapon is nullptr");
		}

		//è®¾å®šæ­¦å™¨ä½ç½®
		Size size = m_sprite->getContentSize();
		m_weapon->setPosition(Vec2(size.width*getWpPos().x, size.height*getWpPos().y));//*getWpPos().x
		m_weapon->setScale(0.08);	//ç”¨äºŽåˆæ¬¡æµ‹è¯•ï¼Œä¹‹åŽåˆ é™¤ï¼Œä¸åŒæ­¦å™¨çš„ç¼©æ”¾ä¸åŒï¼Œè¦ä¹ˆæŠŠç¼©æ”¾æ”¾åœ¨åˆ›å»ºå‡½æ•°é‡Œé¢ï¼Œè¦ä¹ˆå°±æŠŠæ­¦å™¨å›¾ç‰‡çš„å¤§å°è°ƒå¯?

		this->addChild(m_weapon);

		_attack = m_weapon->getAttack();
		return true;
	}
}

void Player::attack(Scene* currentScene,const Vec2& pos) {
	if (_MP - m_weapon->getMpConsume() >= 0) {
		_MP -= m_weapon->getMpConsume();
		this->m_weapon->fire(currentScene, pos);
	}
	/*
	//æ”»å‡»æ–¹å‘
	auto direction = pos - this->getPosition();
	direction.normalize();
	Vec2 test = this->m_weapon->getPosition();

	//åˆ›å»ºå­å¼¹
	auto bullet = Bullet::create(LONGREMOTE, this, direction, currentScene);
	bullet->setScale(1.5);
	bullet->setPosition(Vec2(this->getPositionX(), this->getPositionY()));
	currentScene->addChild(bullet);
	bullet->new_move();
	*/
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

//å’Œé”®ç›˜æŽ§åˆ¶ç›¸å…³çš„å‡½æ•°
void Player::setViewPointByPlayer()
{
	if (m_sprite == NULL)
		return;
	Layer* parent = (Layer*)getParent();

	//µØÍ¼·½¿éÊý
	Size mapTiledNum = m_map->getMapSize();

	//µØÍ¼µ¥¸ö¸ñ×Ó´óÐ¡
	Size tiledSize = m_map->getTileSize();

	//µØÍ¼´óÐ¡
	Size mapSize = Size(mapTiledNum.width*tiledSize.width, mapTiledNum.height*tiledSize.height);

	//ÆÁÄ»´óÐ¡
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//Ö÷½Ç×ø±ê
	Size mapTiledNum = m_map->getMapSize();
  
	Size tiledSize = m_map->getTileSize();

	Size mapSize = Size(mapTiledNum.width*tiledSize.width, mapTiledNum.height*tiledSize.height);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	Point spritePos = getPosition();

	float x = std::max(spritePos.x,visibleSize.width/2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	//Èç¹ûÖ÷½Ç×ø±ê³¬³ö·¶Î§£¬ÔòÈ¡Ö÷½Ç×ø±ê
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	//Ä¿±êµã
	Point desPos = Point(x, y);



	//é”Ÿæ–¤æ‹·é”Ÿæ–¤æ‹·é”Ÿæ–¤æ‹·é”Ÿæ–¤æ‹·ç“¿î„Šæ‹·é”Ÿè½¿Ñæ‹·é”Ÿæ–¤æ‹·é”Ÿé¥ºâ˜…æ‹·é”Ÿæ–¤æ‹·é”Ÿæ–¤æ‹·é”Ÿ?
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	Point desPos = Point(x, y);

	Point centPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	Point viewPos = centPos - desPos;

	parent->setPosition(viewPos);

}

void Player::set_tag_position(int x, int y)
{
	/*ÅÐ¶ÏÇ°ÃæÊÇ·ñ²»¿ÉÍ¨ÐÐ*/
	Size spriteSize = m_sprite->getContentSize();
	Point dstPos = Point(x+spriteSize.width/2, y);
	Point dstPos_y = Point(x + spriteSize.width / 2, y - spriteSize.height / 2);
	//¸Ã×ø±êÎªPlayer¶ÔÓ¦×ø±êÆ«ÏÂµÄÎ»ÖÃ£¬ÎªÁËÅÐ¶ÏPlayerÏÂ·½µÄ½¨ÖþÎï

	/*»ñµÃÖ÷½ÇÇ°·½µØÍ¼¸ñ×ÓÎ»ÖÃ*/
	Point tiledPos = tileCoordForPosition(Point(dstPos.x, dstPos.y));
	Point tiledPos_right = tileCoordForPosition(Point(dstPos.x + spriteSize.width / 2, dstPos.y));
	Point tiledPos_bottom = tileCoordForPosition(Point(dstPos.x, dstPos.y- spriteSize.height / 2));
	//¶Ô¸Ã¾«ÁéËùÔÚ¸ñ×ÓµÄÇ°·½ÅÐ¶Ï£»
	/*»ñµÃµØÍ¼¸ñ×ÓµÄÎ¨Ò»±êÊ¶*/

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

	int x, y;
    x = (pos.x*1.8) / tiledSize.width;

    /*yåæ ‡éœ€è¦è½¬æ¢ä¸€ä¸‹ï¼Œå› ä¸ºåæ ‡ç³»å’Œtiledä¸åŒ*/
	y = (mapTiledNum.height*tiledSize.height - pos.y*1.8) / tiledSize.height;

	/*¸ñ×Ó´ÓÁã¿ªÊ¼*/
	if (x > 0)
		x--;
	if (y > 0)
		y-=0;

	return Point(x, y);
}


