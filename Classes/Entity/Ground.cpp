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

	m_Appearence = cocos2d::Sprite3D::create("model/scene/changing.c3b");

	if (m_Appearence != nullptr){

		m_Appearence->setPosition3D(Vec3(350, 0, 430));
		m_Appearence->setCameraMask((int)CameraFlag::USER1);
		addChild(m_Appearence);
		//m_Appearence->setScale(f);
		return true;
	}

	return false;
}
