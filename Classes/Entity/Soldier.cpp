#include "cocos2d.h"
#include "Soldier.h"
#include "Animate3DWithEvent.h"

USING_NS_CC;

Soldier::Soldier() :m_Speed(200.f), m_ComboStage(CS_IDLE), m_CriticalTime(false), mCriticalAttackCheck(false)
{

}

Soldier::~Soldier()
{

}

bool Soldier::init()
{
	Entity::init();

	m_Appearence = Sprite3D::create("model/knight/knight.c3b");
	
	if (m_Appearence != nullptr){
		m_Appearence->setScale(9);

		m_Appearence->setPosition3D(Vec3(0, 0, 0));
		m_Appearence->setRotation3D(Vec3(0, 90, 0));
		m_Appearence->setCameraMask((int)CameraFlag::USER1);

		addChild(m_Appearence);
	}
	else
		return false;
	
	auto animData = Animation3D::create("model/knight/knight.c3b");
	m_WalkAnim = Animate3D::createWithFrames(animData, 227, 246);
	
	//Register frame event in Attack Anim
	auto temp= Animate3dWithEvent::createWithFrames(animData, 170, 220);
	temp->registerEventOnFrame(180, CC_CALLBACK_0(Soldier::attackFrameCall, this, true));
	temp->registerEventOnFrame(200, CC_CALLBACK_0(Soldier::attackFrameCall, this, false));
	m_AttackAnim = temp;

	temp = Animate3dWithEvent::createWithFrames(animData, 110, 140);
//	temp->registerEventOnFrame(125, CC_CALLBACK_0(Soldier::attackFrameCall, this, true));
//	temp->registerEventOnFrame(135, CC_CALLBACK_0(Soldier::attackFrameCall, this, false));
	m_Attack2Anim = temp;

	m_IdleAnim = Animate3D::createWithFrames(animData, 267, 283);
	m_IdleAnimAction = createAnimAction(m_IdleAnim,true);

	m_Appearence->runAction(m_IdleAnimAction);

	return true;
}

void Soldier::movePos(float deltaMove)
{
	m_Pos.x += (deltaMove * m_Speed);
	m_Appearence->setPosition(m_Pos);
}

//TODO: 检测连击触发的正确性
void Soldier::doAttack()
{
	if (m_ComboStage == CS_IDLE )
	{
		mCriticalAttackCheck = true;
		m_Appearence->stopActionByTag(ACTION_ANIMATION);
		m_ComboStage = CS_ATTACK_I;
		m_Appearence->runAction(createAnimAction(m_AttackAnim, false));
	}
	else
	{
		//Trigger attack command in attack action
		if (m_CriticalTime && mCriticalAttackCheck)
		{
			if (m_ComboStage == CS_ATTACK_I)
				m_ComboStage = CS_ATTACK_II;
		}
		else
		{
			mCriticalAttackCheck = false;
		}
	}
}

void Soldier::attackFinishedCallback(bool state)
{
	if (m_ComboStage != CS_ATTACK_II)
	{
		m_Appearence->runAction(createAnimAction(m_IdleAnim, true));
		m_ComboStage = CS_IDLE;
	}
}

void Soldier::attackFrameCall(bool state)
{
	m_CriticalTime = state;

	//if trigger the combo attack , immedataly start it !
	if (!state)
	{
		if (m_ComboStage == CS_ATTACK_II)
		{
			m_ComboStage = CS_COMBO_LEVEL_COUNT;
			m_Appearence->stopActionByTag(ACTION_ANIMATION);
			m_Appearence->runAction(createAnimAction(m_Attack2Anim, false));
		}
	}
}

