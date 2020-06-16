#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "Entity.h"

class Player:public Entity
{
public:
//by lq
	CREATE_FUNC(Player);
	virtual bool init();
	void run();
	void setViewPointByPlayer();
	virtual void set_tag_position(int x, int y);
	void setTiledMap(TMXTiledMap* map);
private:
//by lq
	TMXTiledMap* m_map;
<<<<<<< HEAD
	bool isJumping;//±ê¼ÇÖ÷½ÌÊÇ·ñÅö×²ÁËÕÏ°­Îï

	TMXLayer* meta;//¼ì²âÅö×²µÄµØÍ¼²ã
	
	/*½«ÏñËØ×ø±ê×ª»¯ÎªµØÍ¼¸ñ×Ó×ø±ê*/
	bool isJumping;//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ç·ï¿½ï¿½ï¿½×²ï¿½ï¿½ï¿½Ï°ï¿½ï¿½ï¿½
	TMXLayer* meta;//ï¿½ï¿½ï¿½ï¿½ï¿½×²ï¿½Äµï¿½Í¼ï¿½ï¿?
	/*ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½×ªï¿½ï¿½Îªï¿½ï¿½Í¼ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½*/
	Point tileCoordForPosition(Point pos);

};

#endif