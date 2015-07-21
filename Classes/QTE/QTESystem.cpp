#include "QTESystem.h"
#include "QteInfo.h"
#include "QteHandlerStandard.h"
#include "QteLayerStandard.h"
#include <utility>

QteSystem* QteSystem::sInstance = nullptr;

QteSystem* QteSystem::getInstance()
{
	assert(sInstance != nullptr);
	return sInstance;
}

void QteSystem::create(Node* node)
{
	assert(sInstance == nullptr);
	sInstance = new QteSystem(node);
}

void QteSystem::destroy()
{
	if (sInstance != nullptr)
		delete sInstance;
}

QteSystem::QteSystem(Node* node) 
	: mState(QTE_STATE::QS_INACTIVE)
	, mSceneNode(node)
	, mCurrInfo(nullptr)
	, mPreSetInfo(nullptr)
{
	//TODO: load qte info
}

QteSystem::~QteSystem()
{
	for (auto itr = mQteMap.begin(); itr != mQteMap.end(); ++itr)
	{
		delete itr->second;
	}

	mQteMap.clear();
}

//The predeifned event
void QteSystem::trigger(const std::string& qteName, std::function<void(QTE_Result)> func)
{
	assert(mPreSetInfo == nullptr);

	//TODO: how we set the params ?
	mPreSetInfo = new QteInfo();
	mPreSetInfo->mType = QTE_TYPE::QTE_Normal;
	trigger(mPreSetInfo);
}

void QteSystem::trigger(const QteInfo* info)
{
	assert(mState == QTE_STATE::QS_INACTIVE);
	mState = QTE_STATE::QS_ACTIVE;

	mCurrInfo = info;
	if (prepare())
	{
		mSceneNode->addChild(mLayer);
		mLayer->prepare(mHander);
	}
	else
	{	
		//TODO
		assert(false);
		finish();
	}


}

void QteSystem::forceFinish()
{
	//Force to end QTE
/*	finish();*/
}

void QteSystem::finish()
{
	mState = QTE_STATE::QS_INACTIVE;

	mCurrInfo = nullptr;
	if (mPreSetInfo != nullptr)
	{
		delete mPreSetInfo;
		mPreSetInfo = nullptr;
	}

	mLayer->removeFromParent();
	assert(mLayer->getReferenceCount() == 1);
	mLayer = nullptr;

	assert(mHander->getReferenceCount() == 1);
	mHander = nullptr;
}

bool QteSystem::prepare()
{
	if (mCurrInfo->mType == QTE_TYPE::QTE_Normal)
	{
		mHander = QteHandlerStandard::create(mCurrInfo);
		mLayer = QteLayerStandard::create();
	}

	return true;
}

void QteSystem::update(float dt)
{
	if ( mState != QTE_STATE::QS_ACTIVE)
		return;

	mHander->update(dt);

	if (mHander->isDone())
	{
		finishing();
	}
}

void QteSystem::finishing()
{
	assert(mState == QTE_STATE::QS_ACTIVE);

	mState = QTE_STATE::QS_FREEZE;

	//TODO:  delay to close QTE
	finish();
}
