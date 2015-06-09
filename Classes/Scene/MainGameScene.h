#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MainGameScene : public cocos2d::Scene
{
CC_CONSTRUCTOR_ACCESS:
	virtual bool init()override;
	MainGameScene()	{}
	~MainGameScene();

public:
	CREATE_FUNC(MainGameScene);

    

protected:
	void update(float dt)override;

	RefPtr<Layer>	mGameLayer;
	RefPtr<Layer>	mUiLayer;

};

#endif // __HELLOWORLD_SCENE_H__
