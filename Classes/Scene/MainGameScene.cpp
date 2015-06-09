#include "MainGameScene.h"
#include "Entity/Soldier.h"
#include "Entity/Ground.h"
#include "QTE/QTESystem.h"

USING_NS_CC;

bool MainGameScene::init()
{
    if ( !Scene::init() )
        return false;

    auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    auto cam = Camera::createPerspective(60, frameSize.width / frameSize.height,1,2000);
    cam->setCameraFlag(CameraFlag::USER1);
    
	//Initial params
    cam->setPosition3D(Vec3(100, 120, 210));
    cam->lookAt(Vec3(100, 25, -20), Vec3(0, 1, 0));
    addChild(cam);
    
	//Init layer for 3d object
	mGameLayer = Layer::create();
	mGameLayer->setCameraMask((int)CameraFlag::USER1);

    auto player = Soldier::create();
	mGameLayer->addChild(player);
    
    auto env = Ground::create();
	mGameLayer->addChild(env);
    
	addChild(mGameLayer);

	//TODO: create a 2d camera for UI here
	auto uiCam = Camera::create();
	uiCam->setCameraFlag(CameraFlag::USER2);
	addChild(uiCam);

	mUiLayer = Layer::create();
	addChild(mUiLayer);
	mUiLayer->setCameraMask((int)CameraFlag::USER2);

	QteSystem::create(mUiLayer);

	scheduleUpdate();

    return true;
}

void MainGameScene::update(float dt)
{
	Node::update(dt);

	QteSystem::getInstance()->update(dt);
}

MainGameScene::~MainGameScene()
{
	QteSystem::destroy();
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
