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
	m_RigidBody = Physics3DRigidBody::create(&rbDes);
	auto component = Physics3DComponent::create(m_RigidBody, Vec3(0.f, -20.f, 0.f));
	component->setBtMask(CM_Soldier);
	component->setBtGroup(ColGroup_Soilder);

	auto sprite = Sprite3D::create("model/knight/knight.c3b");

	sprite->setScale(9);
	sprite->setRotation3D(Vec3(0, 90, 0));
	sprite->setCameraMask((int)CameraFlag::USER1);

	sprite->addComponent(component);
	component->syncNodeToPhysics();
	component->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NODE_TO_PHYSICS);

	//Physics3DGhostObj as volume trigger for QTE
	Physics3DGhostObjDes qteDes;
	qteDes.shape = Physics3DShape::createSphere(100.f);
	auto ghostBody = Physics3DGhostObj::create(&qteDes);

	auto component2 = Physics3DComponent::create(ghostBody, Vec3(0.f,-10.f, 0.f));
	component2->setName("Qte_Phy");	
	component2->setBtMask(CM_SoldierQTE);
	component2->setBtGroup(ColGroup_SoldierQTE);
	sprite->addComponent(component2);
	component2->syncNodeToPhysics();
	component2->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NODE_TO_PHYSICS);


//	rigidBody->setCollisionCallback(CC_CALLBACK_1(Soldier::hitCallback,this));
//	ghostBody->setCollisionCallback(CC_CALLBACK_1(Soldier::qteTriggerCallback, this));

	m_RigidBody->setMask(CM_Soldier);
	ghostBody->setMask(CM_SoldierQTE);

	m_RigidBody->setUserData(this);
	ghostBody->setUserData(this);

	m_Appearence = sprite;
	addChild(m_Appearence);


	auto animData = Animation3D::create("model/knight/knight.c3b");
	m_WalkAnim = Animate3D::createWithFrames(animData, 227, 246);
	
	//Register frame event in Attack Anim
	auto temp= Animate3dWithEvent::createWithFrames(animData, 180, 220);
// 	temp->registerEventOnFrame(195, CC_CALLBACK_0(Soldier::attackFrameCall, this, true));
// 	temp->registerEventOnFrame(200, CC_CALLBACK_0(Soldier::attackFrameCall, this, false));
	m_AttackAnim = temp;

	temp = Animate3dWithEvent::createWithFrames(animData, 110, 140);
	m_Attack2Anim = temp;

	m_IdleAnim = Animate3D::createWithFrames(animData, 267, 283);
	m_IdleAnimAction = createAnimAction(m_IdleAnim,true);

	m_KnockAnim = Animate3D::createWithFrames(animData, 81, 87);

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

		CCLOG("Sword Attack I");
//		QteSystem::getInstance()->trigger("",nullptr);
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

void Soldier::hitCallback(const Physics3DCollisionInfo &ci)
{
	if (ci.objB->getMask() == CM_Slime)
	{
		CCLOG("Ouch, i'm hurt!!!!");
	}

}

void Soldier::qteTriggerCallback(const Physics3DCollisionInfo &ci)
{
	if (ci.objB->getMask() == CM_Slime)
	{
		CCLOG("Ouch,QTE!!!!");
	}
}

void Soldier::doHurt()
{
	m_Appearence->stopActionByTag(ACTION_ANIMATION);
	m_Appearence->runAction(createAnimAction(m_KnockAnim, false));
}

