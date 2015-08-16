#include "Slime.h"

Slime::Slime() :mAttackState(AttackState::AS_READY)
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

	auto rigidBody = Physics3DRigidBody::create(&rbDes);
	Quaternion quat;
	Quaternion::createFromAxisAngle(Vec3(0.f, 1.f, 0.f), CC_DEGREES_TO_RADIANS(180), &quat);
	auto component = Physics3DComponent::create(rigidBody, Vec3(0.f, -10.f, 0.f)/*,quat*/);
	rigidBody->setMask(CollisionMask::CM_Slime);

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
		auto phyCom = static_cast<Physics3DComponent*>(m_Appearence->getComponent(Physics3DComponent::getPhysics3DComponentName()));
		auto rigidBody = static_cast<Physics3DRigidBody*>(phyCom->getPhysics3DObject());

		rigidBody->setLinearFactor(Vec3::ONE);

		Vec3 rushVec(sPlayer->getNode()->getPosition3D());
		rushVec.subtract(m_Appearence->getPosition3D());
		rushVec.y = -rushVec.x / 5;
		rigidBody->setLinearVelocity(rushVec);

		rigidBody->setAngularVelocity(Vec3::ZERO);
		rigidBody->setCcdMotionThreshold(0.5f);
		rigidBody->setCcdSweptSphereRadius(0.4f);

		rigidBody->setActive(true);
	}

}


