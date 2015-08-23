#ifndef __QTE_HANDLER_H__
#define __QTE_HANDLER_H__

#include "cocos2d.h"
#include "QteInfo.h"

USING_NS_CC;

#define CREATE_FUNC_QTE_HANDLER(__TYPE__,__QTE_INFO__) \
static __TYPE__* create(const __QTE_INFO__* info) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(info); \
    if (pRet) \
		    { \
        pRet->autorelease(); \
        return pRet; \
		    } \
			    else \
			    { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
			    } \
}


class QteHandler : public Ref{
CC_CONSTRUCTOR_ACCESS:
	QteHandler(const QteInfo* info);
	virtual ~QteHandler();

public:
	//Player do sth operations on GUI, this is the feedback
	virtual void onGuiCallback() = 0;

	virtual void update(float dt);

	virtual bool isDone();

	QTE_Result getResult()const { return mResult; }

protected:
	bool		mIsFinished;
	QTE_Result	mResult;

	//TSR - TimeScaleRate
	float		mCurrTSR;
	float		mTSR_SlowdownSpd;
	float		mTSR_RegainSpd;

	float		mTimeLeft;

	const QteInfo*	mQteInfo;

};

#endif