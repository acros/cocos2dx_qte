#ifndef __QTE_SYSTEM_H__
#define __QTE_SYSTEM_H__

#include "cocos2d.h"

USING_NS_CC;

class QteHandler;

class QteSystem{
CC_CONSTRUCTOR_ACCESS:
	friend class GameWorld;
	
	static void create();
	static void destroy();

	QteSystem();
	~QteSystem();

public:
	static QteSystem*	getInstance();

	void trigger(const std::string& qteName);
	void forceFinish();


protected:
	bool					mActive;

	RefPtr<Layer>			mLayer;
	RefPtr<QteHandler>		mHander;

	static QteSystem*	sInstance;
};


#endif