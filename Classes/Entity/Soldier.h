#ifndef __ENTITY_SOLDIER_H__
#define __ENTITY_SOLDIER_H__

#include "Entity.h"

//Simple combo check
enum ComboState{
	CS_IDLE,
	CS_ATTACK_I,
	CS_ATTACK_II,
	CS_COMBO_LEVEL_COUNT
};


class Soldier : public Entity{
CC_CONSTRUCTOR_ACCESS:
	Soldier();
	~Soldier();
	virtual bool init()override;

public:
	CREATE_FUNC(Soldier);

	void movePos(float dm);
	void doAttack();
	void doHurt();

protected:
	
	virtual void hitCallback(const Physics3DCollisionInfo &ci);
	virtual	void qteTriggerCallback(const Physics3DCollisionInfo &ci);

private:
	virtual void attackFinishedCallback(bool state);

	void attackFrameCall(bool state);

	//Ignore the Z-axis
	cocos2d::Vec2	m_Pos;

	//Animation
	cocos2d::RefPtr<cocos2d::Animate3D>	m_IdleAnim;
	cocos2d::RefPtr<cocos2d::Animate3D>	m_AttackAnim;
	cocos2d::RefPtr<cocos2d::Animate3D>	m_Attack2Anim;
// 	cocos2d::RefPtr<cocos2d::Animate3D>	m_SpecialAttackAnim;
// 	cocos2d::RefPtr<cocos2d::Animate3D>	m_SpecialAttack2Anim;
	cocos2d::RefPtr<cocos2d::Animate3D>	m_DefendAnim;
	cocos2d::RefPtr<cocos2d::Animate3D>	m_KnockAnim;

	cocos2d::RefPtr<cocos2d::Animate3D>	m_WalkAnim;
	cocos2d::RefPtr<cocos2d::Animate3D>	m_DeadAnim;


	float	m_Speed;

	bool		mCriticalAttackCheck;
	bool		m_CriticalTime;
	ComboState	m_ComboStage;
};

#endif

/*
	Piglet._action = 
	{
		idle = createAnimation(file, 0, 40, 0.7),
		walk = createAnimation(file, 135, 147, 1.5),
		attack1 = createAnimation(file, 45, 60, 0.7),
		attack2 = createAnimation(file, 60, 75, 0.7),
		defend = createAnimation(file, 92, 96, 0.7),
		knocked = createAnimation(file, 81, 87, 0.7),
		dead = createAnimation(file, 95, 127, 1)
	}


*/