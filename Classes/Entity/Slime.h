#ifndef _ENTITY_SLIME_H__
#define _ENTITY_SLIME_H__

#include "Entity.h"
#include "physics3d/CCPhysics3DObject.h"
#include "QTE/QTESystem.h"

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
	virtual void resetGame()override;

protected:
	virtual	void collisionCallback(const Physics3DCollisionInfo &ci);
	void qteCallback(QTE_Result result);

	enum class AttackState
	{
		AS_ATTACKING,
		AS_SLEEPING,
		AS_READY,
		AS_FAIL,
	}		mAttackState;


	bool	 m_CanTriggerQTE;

	QteInfo	m_AttackQteInfo;
	class Soldier*	m_QteTarget;
};


#endif