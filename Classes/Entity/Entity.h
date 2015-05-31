#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "EntityUtils.h"
#include "cocos2d.h"

class Entity : public cocos2d::Node{
CC_CONSTRUCTOR_ACCESS:
	Entity();
	virtual ~Entity();

	virtual bool init();
public:
//	CREATE_FUNC(Entity);


protected:
	virtual void attackFinishedCallback(bool state);
	cocos2d::Action*	createAnimAction(cocos2d::Animate3D*,bool loop = true);
	
	
	cocos2d::RefPtr<cocos2d::Action>	m_IdleAnimAction;

	//Sprite3D or Sprite
	cocos2d::Node*	m_Appearence;
};

#endif