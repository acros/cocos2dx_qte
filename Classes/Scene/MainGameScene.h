#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MainGameScene : public cocos2d::Scene
{
CC_CONSTRUCTOR_ACCESS:
	virtual bool init()override;

public:
	CREATE_FUNC(MainGameScene);

	void gameExitMsgCallback(cocos2d::Ref* pSender);
    

protected:
	RefPtr<Layer>	mGameLayer;

};

#endif // __HELLOWORLD_SCENE_H__
