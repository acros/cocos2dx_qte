#ifndef __GAME_WORLD_H__
#define __GAME_WORLD_H__

#include "cocos2d.h"

USING_NS_CC;

class GameWorld{
public:
	GameWorld();
	~GameWorld();

	void createGame();
	void runGame();
	void quitGame();

protected:

	RefPtr<Scene>		mCurrScene;
};

#endif