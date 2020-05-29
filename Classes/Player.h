#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "Entity.h"

class Player:public Entity
{
public:
	CREATE_FUNC(Player);
	virtual bool init();
	void run();
};

#endif