#ifndef __QTE_INFO_H__
#define __QTE_INFO_H__

#include "base/ccConfig.h"

class QteInfo{
	friend class QteHandler;
	friend class QteSystem;

CC_CONSTRUCTOR_ACCESS:
	QteInfo();
	~QteInfo();
	
protected:

	//The total time of this QTE
	float	mDuration;

	//Before player can take action 
	float	mStartingDuration;

	//After player take action, before the QTE ends
	float	mEndingDuration;

	//The duration of player can taking actions
	float	mAvailableDuration;

	//The minimum rate of time scale
	float	mMinTimeScale;	
};


#endif