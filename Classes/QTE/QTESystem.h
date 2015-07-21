#ifndef __QTE_SYSTEM_H__
#define __QTE_SYSTEM_H__

#include "cocos2d.h"
#include "QteLayer.h"
#include "QteHandler.h"

USING_NS_CC;

enum class QTE_Result;
class QteInfo;

class QteSystem{
CC_CONSTRUCTOR_ACCESS:
	friend class MainGameScene;
	
	static void create(Node* node);
	static void destroy();

	QteSystem(Node* node);
	~QteSystem();

public:
	static QteSystem*	getInstance();

	//Use the predefined data
	void trigger(const std::string& qteName, std::function<void(QTE_Result)> func);

	//Calculating QTE info in runtime
	void trigger(const class QteInfo*	info);

	void update(float dt);

	void forceFinish();


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

	QteInfo*				mPreSetInfo;
	const QteInfo*			mCurrInfo;
	std::map<const std::string, QteInfo*>	mQteMap;

	

	Node*	mSceneNode;
	static QteSystem*	sInstance;
};


#endif