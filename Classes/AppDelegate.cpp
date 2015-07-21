#include "AppDelegate.h"
#include "GameWorld.h"

USING_NS_CC;

#if defined( _DEBUG )
#define	BUILD_DEBUG	"DEBUG"
#else
#define	BUILD_DEBUG "RELEASE"
#endif

class GameVersion {
public:
	GameVersion(void) { 
		sprintf(text, " [%s - %s] [%s][%s]", __DATE__, __TIME__, BUILD_DEBUG,cocos2dVersion());
	}

	char	text[256];
}	gGameVersion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
	mGameWorld.quitGame();
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::createWithRect("cocos2d-x QTE"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
			+ std::string(gGameVersion.text)
#endif
			, Rect(0,0,1136,640)
			,1
			);

        director->setOpenGLView(glview);
		glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::FIXED_WIDTH);
	}


    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);


    register_all_packages();

	mGameWorld.createGame();
	mGameWorld.runGame();

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
