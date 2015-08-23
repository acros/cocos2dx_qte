#include "Entity.h"

USING_NS_CC;

Entity* Entity::sPlayer = nullptr;

short Entity::ColGroup_Ground = CM_Soldier | CM_Slime | CM_SoldierQTE;
short Entity::ColGroup_Soilder = CM_Ground | CM_Slime;
short Entity::ColGroup_Slime = CM_Soldier | CM_Ground | CM_SoldierQTE;
short Entity::ColGroup_SoldierQTE = CM_Ground | CM_Slime;


Entity::Entity() :m_Appearence(nullptr), m_RigidBody(nullptr)
{
}

Entity::~Entity()
{
}

bool Entity::init()
{
	return Node::init();
}

Action* Entity::createAnimAction(Animate3D* anim,bool loop)
{
	Action* act = nullptr;
	
	if (loop)
		act = RepeatForever::create(anim);
	else
	{
		act = Sequence::create(Repeat::create(anim,1), CallFuncN::create(CC_CALLBACK_0(Entity::attackFinishedCallback, this, true)), nullptr);
	}

	act->setTag(ACTION_ANIMATION);
	return act;
}

void Entity::attackFinishedCallback(bool state)
{
	if (state)
	{
		m_Appearence->runAction(m_IdleAnimAction);
	}
}