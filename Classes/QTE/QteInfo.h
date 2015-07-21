#ifndef __QTE_INFO_H__
#define __QTE_INFO_H__

#include "base/ccConfig.h"

enum class QTE_Result
{
	QTE_FAILED,
	QTE_SUCCEED,

};

enum class QTE_TYPE
{
	QTE_Normal,
};

class QteInfo{
	friend class QteHandler;
	friend class QteSystem;

CC_CONSTRUCTOR_ACCESS:
	QteInfo();
	~QteInfo();
	
protected:

	QTE_TYPE mType;

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