#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "Entity.h"

class Player:public Entity
{
public:
	CREATE_FUNC(Player);
	virtual bool init();
	void run();
	void setViewPointByPlayer();
	virtual void set_tag_position(int x, int y);
	void setTiledMap(TMXTiledMap* map);
private:
	TMXTiledMap* m_map;
	bool isJumping;//标记主教是否碰撞了障碍物

	TMXLayer* meta;//检测碰撞的地图层
	
	/*将像素坐标转化为地图格子坐标*/
	Point tileCoordForPosition(Point pos);
};

#endif