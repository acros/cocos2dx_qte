#include "Ground.h"
#include "3d/CCSprite3D.h"
#include "2d/CCCamera.h"

USING_NS_CC;

Ground::Ground()
{

}

Ground::~Ground()
{

}

bool Ground::init()
{
	Entity::init();

	Physics3DRigidBodyDes rbDes;
	rbDes.mass = 0.0f;
	rbDes.shape = Physics3DShape::createBox(Vec3(1000.f,0.5f,1000.f));

	auto sprite = PhysicsSprite3D::create("model/scene/changing.c3b", &rbDes);
	sprite->getPhysicsObj()->setMask(CollisionMask::CM_Ground);
	sprite->setPosition3D(Vec3(350, 0, 430));
	sprite->setCameraMask((int)CameraFlag::USER1);
	sprite->syncNodeToPhysics();
	sprite->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NONE);

	auto phyCom = static_cast<Physics3DComponent*>(sprite->getComponent(Physics3DComponent::getPhysics3DComponentName()));
	phyCom->setBtMask(CM_Ground);
	phyCom->setBtGroup(ColGroup_Soilder);

	m_Appearence = sprite;
	addChild(m_Appearence);


	return true;
}
