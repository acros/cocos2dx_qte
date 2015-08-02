#include "cocos2d.h"
#include "Soldier.h"
#include "EngineEx/Animate3DWithEvent.h"
#include "QTE/QTESystem.h"


USING_NS_CC;

Soldier::Soldier() :m_Speed(200.f), m_ComboStage(CS_IDLE), m_CriticalTime(false), mCriticalAttackCheck(false)
{
	assert(sPlayer == nullptr);
	sPlayer = this;
}

Soldier::~Soldier()
{
	sPlayer = nullptr;
}

bool Soldier::init()
{
	Entity::init();

	//Prepare for Physics
	Physics3DRigidBodyDes rbDes;
	rbDes.mass = 500.0f;
	rbDes.shape = Physics3DShape::createCapsule(10.f, 25.f);
	auto rigidBody = Physics3DRigidBody::create(&rbDes);
	auto component = Physics3DComponent::create(rigidBody, Vec3(0.f, -20.f, 0.f));

	auto sprite = Sprite3D::create("model/knight/knight.c3b");

	sprite->setScale(9);
	sprite->setRotation3D(Vec3(0, 90, 0));
	sprite->setCameraMask((int)CameraFlag::USER1);

	sprite->addComponent(component);
	component->syncNodeToPhysics();
	component->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NODE_TO_PHYSICS);

	m_Appearence = sprite;
	addChild(m_Appearence);

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

//TODO: Check the combo
void Soldier::doAttack()
{
	if (m_ComboStage == CS_IDLE )
	{
		mCriticalAttackCheck = true;
		m_Appearence->stopActionByTag(ACTION_ANIMATION);
		m_ComboStage = CS_ATTACK_I;
		m_Appearence->runAction(createAnimAction(m_AttackAnim, false));

		CCLOG("Attack start");
		QteSystem::getInstance()->trigger("",nullptr);

	}
	else
	{
		//Trigger attack command in attack action
		if (m_CriticalTime && mCriticalAttackCheck)
		{
			CCLOG("Trigger combo!");

			if (m_ComboStage == CS_ATTACK_I)
				m_ComboStage = CS_ATTACK_II;
		}
		else
		{
			CCLOG("Combo failed");
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

