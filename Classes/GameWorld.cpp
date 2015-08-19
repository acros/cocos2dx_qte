#include "GameWorld.h"
#include "QTE/QTESystem.h"

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
}

void GameWorld::createGame()
{
	mCurrScene = MainGameScene::create();
}

void GameWorld::runGame()
{
	Director::getInstance()->runWithScene(mCurrScene);
}

void GameWorld::quitGame()
{
	mCurrScene = nullptr;
}

void GameWorld::reset()
{
	if (mCurrScene != nullptr)
	{
		mCurrScene->resetGame();
	}
}

