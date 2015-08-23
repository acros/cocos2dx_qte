#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "physics3d/CCPhysics3D.h"
#include "EntityUtils.h"
#include "cocos2d.h"

USING_NS_CC;

class Entity : public cocos2d::Node{
CC_CONSTRUCTOR_ACCESS:
	enum CollisionMask
	{
		CM_Unknown = 0,
		CM_Ground = 1 << 1,
		CM_Soldier = 1 << 2,
		CM_Slime = 1 << 3,
		CM_SoldierQTE = 1 << 4
	};

	static short ColGroup_Ground;
	static short ColGroup_Soilder;
	static short ColGroup_Slime;
	static short ColGroup_SoldierQTE;

	Entity();
	virtual ~Entity();

	virtual bool init();

	virtual void resetGame()	{}

public:
//	CREATE_FUNC(Entity);

	Node*	getNode()const { return m_Appearence; }

protected:
	virtual void attackFinishedCallback(bool state);
	Action*	createAnimAction(Animate3D*, bool loop = true);


	RefPtr<cocos2d::Action>	m_IdleAnimAction;

	//Sprite3D or Sprite
	Node*	m_Appearence;
	Physics3DRigidBody*	m_RigidBody;

	static Entity*	sPlayer;
};

#endif