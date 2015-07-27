#include "GameWorld.h"
#include "Scene/MainGameScene.h"
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

