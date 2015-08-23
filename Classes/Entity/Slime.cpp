#include "Slime.h"
#include "QTE/QTESystem.h"
#include "Soldier.h"

Slime::Slime() :mAttackState(AttackState::AS_READY), m_CanTriggerQTE(true), m_QteTarget(nullptr)
{

}

Slime::~Slime()
{

}

bool Slime::init()
{
	Entity::init();

	Physics3DRigidBodyDes rbDes;
	rbDes.mass = 10.0f;
	rbDes.shape = Physics3DShape::createSphere(13.f);

	m_RigidBody = Physics3DRigidBody::create(&rbDes);
	Quaternion quat;
	Quaternion::createFromAxisAngle(Vec3(0.f, 1.f, 0.f), CC_DEGREES_TO_RADIANS(180), &quat);
	auto component = Physics3DComponent::create(m_RigidBody, Vec3(0.f, -10.f, 0.f)/*,quat*/);
	m_RigidBody->setMask(CollisionMask::CM_Slime);
	m_RigidBody->setCollisionCallback(CC_CALLBACK_1(Slime::collisionCallback, this));
	m_RigidBody->setUserData(this);
	m_RigidBody->setLinearFactor(Vec3(1, 1, 1));
	m_RigidBody->setFriction(0.5f);
	m_RigidBody->setAngularVelocity(Vec3::ZERO);
	m_RigidBody->setCcdMotionThreshold(0.5f);
	m_RigidBody->setCcdSweptSphereRadius(0.4f);

	component->setBtMask(CM_Slime);
	component->setBtGroup(ColGroup_Slime);

	auto sprite = Sprite3D::create("model/slime/slime.c3b", "model/slime/baozi.jpg");
	sprite->addComponent(component);
	sprite->setScale(9);
	sprite->setPosition3D(Vec3(200, 0, 0));
	sprite->setRotation3D(Vec3(0, -90, 0));
	sprite->setCameraMask((int)CameraFlag::USER1);
	component->syncNodeToPhysics();
	component->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE);

	m_Appearence = sprite;
	addChild(m_Appearence);

	return true;
}

void Slime::attack()
{
	if (mAttackState == AttackState::AS_READY)
	{
		CCLOG("Slime Attack");
// 		auto phyCom = static_cast<Physics3DComponent*>(m_Appearence->getComponent(Physics3DComponent::getPhysics3DComponentName()));
// 		auto rigidBody = static_cast<Physics3DRigidBody*>(phyCom->getPhysics3DObject());

		Vec3 rushVec(sPlayer->getNode()->getPosition3D());
		rushVec.subtract(m_Appearence->getPosition3D());
		rushVec.y = -rushVec.x / 5;
		m_RigidBody->setLinearVelocity(rushVec);
		m_RigidBody->setActive(true);
	}

}

void Slime::collisionCallback(const Physics3DCollisionInfo &ci)
{
	if (ci.objA->getMask() == CM_SoldierQTE && m_CanTriggerQTE)
	{
		m_CanTriggerQTE = false;

		//Compute the QTE params
		m_AttackQteInfo.mActive = true;
		m_AttackQteInfo.mDuration = 0.1f;	// HACK: 0.3s for QTE reaction (no time scale)
		m_AttackQteInfo.mMinTimeScale = 0.2f;
		m_AttackQteInfo.mAvailableDuration = m_AttackQteInfo.mDuration;
		m_AttackQteInfo.mType = QTE_TYPE::QTE_Click;

		m_QteTarget = static_cast<Soldier*>(ci.objA->getUserData());
		m_QteTarget->doAttack();

		QteSystem::getInstance()->trigger(m_AttackQteInfo,CC_CALLBACK_1(Slime::qteCallback,this));
	}

	if (ci.objA->getMask() == CM_Soldier)
	{
		if (mAttackState == AttackState::AS_FAIL)
		{
			m_RigidBody->setLinearVelocity(Vec3(400, 100, 0));
		}

		if (m_AttackQteInfo.mActive)
		{
			//Fail the QTE
			QteSystem::getInstance()->forceFinish(QTE_Result::QTE_FAILED);

			m_AttackQteInfo.mActive = false;
		}
	}
}

void Slime::resetGame()
{
	m_AttackQteInfo.mActive = false;
	m_CanTriggerQTE = true; 
	
	mAttackState = AttackState::AS_READY;
	auto phyCom = static_cast<Physics3DComponent*>(m_Appearence->getComponent(Physics3DComponent::getPhysics3DComponentName()));
	m_Appearence->setPosition3D(Vec3(200, 0, 0));
	m_Appearence->setRotation3D(Vec3(0, -90, 0));
	phyCom->syncNodeToPhysics();

	m_RigidBody->setLinearVelocity(Vec3::ZERO);
	m_RigidBody->setAngularVelocity(Vec3::ZERO);

	phyCom->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE);
}

void Slime::qteCallback(QTE_Result result)
{
	m_AttackQteInfo.mActive = false;
	if (result == QTE_Result::QTE_FAILED)
	{
		m_QteTarget->doHurt();
	}
	else
	{
		mAttackState = AttackState::AS_FAIL;
	}

	m_QteTarget = nullptr;
}


