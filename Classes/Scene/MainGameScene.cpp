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
    cam->setPosition3D(Vec3(100, 120, 210));
    cam->lookAt(Vec3(100, 25, -20), Vec3(0, 1, 0));
    addChild(cam);
    
	//Init layer for 3d object
	mGameLayer = Layer::create();
	addChild(mGameLayer);
	mGameLayer->setCameraMask((int)CameraFlag::USER1);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	enableDebugInput();
#endif

    auto player = Soldier::create();
	mGameLayer->addChild(player);
    
    auto env = Ground::create();
	mGameLayer->addChild(env);

	//2D camera and layout
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

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
void MainGameScene::enableDebugInput()
{
	auto keyEvt = EventListenerKeyboard::create();
	keyEvt->onKeyPressed = CC_CALLBACK_2(MainGameScene::onKeyPress, this);
	keyEvt->onKeyReleased = CC_CALLBACK_2(MainGameScene::onKeyRelease, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyEvt, mGameLayer);
}

void MainGameScene::onKeyPress(EventKeyboard::KeyCode code, Event* ev)
{
	if (code == EventKeyboard::KeyCode::KEY_F1)
	{
		QteSystem::getInstance()->trigger("");
	}
}

#endif
