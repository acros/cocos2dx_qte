#ifndef __QTE_HANDLER_H__
#define __QTE_HANDLER_H__

#include "cocos2d.h"
#include "QteInfo.h"


class QteHandler{
CC_CONSTRUCTOR_ACCESS:
	QteHandler(const QteInfo* info);
	virtual ~QteHandler();

public:
	//Player do sth operations on GUI, this is the feedback
	virtual void onGuiCallback() = 0;

	virtual void update(float dt);


protected:
	//TSR - TimeScaleRate
	float		mCurrTSR;
	float		mTSR_SlowdownSpd;
	float		mTSR_RegainSpd;

	float		mTimeLeft;

	const QteInfo*	mQteInfo;

};

#endif