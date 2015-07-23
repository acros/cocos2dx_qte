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
}

void GameWorld::runGame()
{
	//MainGameScene::create()
	auto x = new MainGameScene();
	x->init();
	Director::getInstance()->runWithScene(x);
}

void GameWorld::quitGame()
{
}

