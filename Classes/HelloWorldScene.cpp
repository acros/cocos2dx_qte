#include "HelloWorldScene.h"
#include "Entity/Soldier.h"
#include "Entity/Ground.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    auto cam = Camera::createPerspective(60, frameSize.width / frameSize.height,1,2000);
    cam->setCameraFlag(CameraFlag::USER1);
    this->setCameraMask((int)CameraFlag::USER1);
    
    cam->setPosition3D(Vec3(100, 120, 210));
    cam->lookAt(Vec3(100, 25, -20), Vec3(0, 1, 0));
    addChild(cam);
    
    
    //Init 3d world
    auto player = Soldier::create();
    addChild(player);
    
    auto env = Ground::create();
    addChild(env);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
