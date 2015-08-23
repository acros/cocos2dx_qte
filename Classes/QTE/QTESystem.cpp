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
	, m_CallBackFunc(nullptr)
//	, mPreSetInfo(nullptr)
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

void QteSystem::trigger(const std::string& qteName, QTE_CALLBACK_FUNC func)
{
	assert(false);
	assert(mCurrInfo.mActive);

	//Find the predeifned event
// 	mPreSetInfo->mType = QTE_TYPE::QTE_Click;
/*	trigger(mPreSetInfo);*/
}

void QteSystem::trigger(const QteInfo& info,QTE_CALLBACK_FUNC func)
{
	assert(mState == QTE_STATE::QS_INACTIVE);
	mState = QTE_STATE::QS_ACTIVE;

	mResult = QTE_Result::QTE_FAILED;
	m_CallBackFunc = func;
	mCurrInfo = info;

	m_TimeScaler.setScaling(mCurrInfo.mMinTimeScale,mCurrInfo.mDuration,false,TimeScalePriority::TSP_QTE);

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

void QteSystem::forceFinish(QTE_Result result /*= QTE_Result::QTE_FAILED*/)
{
	if (mState != QTE_STATE::QS_ACTIVE)
		return;

	finish();
}

void QteSystem::finish()
{
	mState = QTE_STATE::QS_INACTIVE;

	mLayer->removeFromParent();
	assert(mLayer->getReferenceCount() == 1);
	mLayer = nullptr;

	assert(mHander->getReferenceCount() == 1);
	mHander = nullptr;

	m_TimeScaler.reset();

	if (m_CallBackFunc != nullptr)
		m_CallBackFunc(mResult);

	m_CallBackFunc = nullptr;

}

bool QteSystem::prepare()
{
	if (mCurrInfo.mType == QTE_TYPE::QTE_Click)
	{
		mHander = QteHandlerStandard::create(&mCurrInfo);
		mLayer = QteLayerStandard::create();
	}

	return true;
}

void QteSystem::update(float dt)
{
	if ( mState != QTE_STATE::QS_ACTIVE)
		return;

	mHander->update(dt);
	m_TimeScaler.update(dt);

	if (mHander->isDone())
	{
		mResult = mHander->getResult();
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
