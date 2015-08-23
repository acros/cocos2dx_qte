#ifndef __QTE_SYSTEM_H__
#define __QTE_SYSTEM_H__

#include "cocos2d.h"
#include "QteLayer.h"
#include "QteHandler.h"
#include "QteInfo.h"
#include "TimeScaler/TimeScaler.h"

USING_NS_CC;

enum class QTE_Result;
class QteInfo;

typedef  std::function<void(QTE_Result)>  QTE_CALLBACK_FUNC;

class QteSystem{
CC_CONSTRUCTOR_ACCESS:
	friend class MainGameScene;
	
	static void create(Node* node);
	static void destroy();

	QteSystem(Node* node);
	~QteSystem();

public:
	static QteSystem*	getInstance();

	bool isActive()const { return mState == QTE_STATE::QS_ACTIVE; }

	//Use the predefined data
	void trigger(const std::string& qteName, QTE_CALLBACK_FUNC func = nullptr);

	//Calculating QTE info in runtime
	void trigger(const class QteInfo&	info, QTE_CALLBACK_FUNC func = nullptr);

	void update(float dt);

	void forceFinish(QTE_Result result = QTE_Result::QTE_FAILED);

protected:

	bool prepare();
	void finishing();
	void finish();

	enum class QTE_STATE{
		QS_INACTIVE,		// QTE is not working
		QS_ACTIVE,			// QTE is running
		QS_FREEZE,			// Waiting for something finishing job done (Mostly in QteLayer)
	}	mState;

	RefPtr<QteLayer>		mLayer;
	RefPtr<QteHandler>		mHander;

	QTE_Result				mResult;
	QteInfo					mCurrInfo;
	std::map<const std::string, QteInfo*>	mQteMap;

	QTE_CALLBACK_FUNC		m_CallBackFunc;
	Node*	mSceneNode;

	TimeScaler			m_TimeScaler;
	static QteSystem*	sInstance;
};


#endif