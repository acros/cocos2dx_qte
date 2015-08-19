#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MainGameScene : public Scene
{
CC_CONSTRUCTOR_ACCESS:
	virtual bool init()override;
	MainGameScene()	{}
	~MainGameScene();

public:
	CREATE_FUNC(MainGameScene);

	void resetGame();

private:
	CC_DISALLOW_COPY_AND_ASSIGN(MainGameScene);

protected:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	void enableDebugInput();

	void onKeyPress(EventKeyboard::KeyCode code, Event* ev);
	void onKeyRelease(EventKeyboard::KeyCode code, Event* ev)	{}

#endif

	void update(float dt)override;

	RefPtr<Layer>	mGameLayer;
	RefPtr<Layer>	mUiLayer;

};

#endif // __HELLOWORLD_SCENE_H__
