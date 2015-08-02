#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "physics3d/CCPhysics3D.h"
#include "EntityUtils.h"
#include "cocos2d.h"

USING_NS_CC;

class Entity : public cocos2d::Node{
CC_CONSTRUCTOR_ACCESS:
	Entity();
	virtual ~Entity();

	virtual bool init();
public:
//	CREATE_FUNC(Entity);

	Node*	getNode()const { return m_Appearence; }

protected:
	virtual void attackFinishedCallback(bool state);
	Action*	createAnimAction(Animate3D*, bool loop = true);


	RefPtr<cocos2d::Action>	m_IdleAnimAction;

	//Sprite3D or Sprite
	Node*	m_Appearence;

	static Entity*	sPlayer;
};

#endif