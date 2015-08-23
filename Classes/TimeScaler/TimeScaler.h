#ifndef __TIME_SCALER_H__
#define __TIME_SCALER_H__

#include "cocos2d.h"

USING_NS_CC;

enum class TimeScalePriority
{
	TSP_Unknown,
	TSP_QTE,
	TSP_DEBUG
};

enum class TimeScaleState
{
	Fixed,
	SlowDown,
	Regain
};

class TimeScaler
{
public:
	TimeScaler();
	~TimeScaler();

	void update(float dt);
	bool setScale(float t,TimeScalePriority tsp);
	bool setScaling(float targetScale,float originSpendTime,bool autoRegain,TimeScalePriority tsp = TimeScalePriority::TSP_Unknown);
	void reset(bool forceReset = true, TimeScalePriority tsp = TimeScalePriority::TSP_Unknown);

	float getScale()const { return m_CurrScale; }

CC_CONSTRUCTOR_ACCESS:
	CC_DISALLOW_COPY_AND_ASSIGN(TimeScaler);

protected:
	TimeScaleState		m_State;
	TimeScalePriority	m_CurrPriority;
	float m_CurrScale;

	//Assume all  < 1
	float m_TargetScale;
	float m_Rate;
	bool m_AutoRegain;

};

#endif