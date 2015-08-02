#include "Entity.h"

USING_NS_CC;

Entity* Entity::sPlayer = nullptr;


Entity::Entity() :m_Appearence(nullptr)
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

