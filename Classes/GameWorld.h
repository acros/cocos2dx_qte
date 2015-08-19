#ifndef __GAME_WORLD_H__
#define __GAME_WORLD_H__

#include "cocos2d.h"
#include "Scene/MainGameScene.h"

USING_NS_CC;

class GameWorld{
public:
	GameWorld();
	~GameWorld();

	void createGame();
	void runGame();
	void quitGame();

	void reset();

protected:

	RefPtr<MainGameScene>		mCurrScene;
};

#endif