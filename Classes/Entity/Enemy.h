#ifndef _ENTITY_ENEMY_H__
#define _ENTITY_ENEMY_H__

#include "Entity.h"


class Enemy : public Entity
{
CC_CONSTRUCTOR_ACCESS:
	Soldier();
	~Soldier();
	virtual bool init()override;

public:



};


#endif