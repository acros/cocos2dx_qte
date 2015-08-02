#ifndef _ENTITY_SLIME_H__
#define _ENTITY_SLIME_H__

#include "Entity.h"

USING_NS_CC;

class Slime : public Entity
{
CC_CONSTRUCTOR_ACCESS:
	Slime();
	~Slime();
	virtual bool init()override;

public:
	CREATE_FUNC(Slime);

	void attack();

protected:

	enum class AttackState
	{
		AS_ATTACKING,
		AS_SLEEPING,
		AS_READY,
	}		mAttackState;

};


#endif