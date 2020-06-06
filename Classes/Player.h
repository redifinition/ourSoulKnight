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
	bool isJumping;//�������Ƿ���ײ���ϰ���
	TMXLayer* meta;//�����ײ�ĵ�ͼ��
	/*���������ת��Ϊ��ͼ�������*/
	Point tileCoordForPosition(Point pos);

};

#endif