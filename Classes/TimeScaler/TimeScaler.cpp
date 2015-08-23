#include "TimeScaler.h"

TimeScaler::TimeScaler() 
	: m_CurrScale(1.f)
	, m_CurrPriority(TimeScalePriority::TSP_Unknown)
	, m_State(TimeScaleState::Fixed)
	, m_TargetScale(1.f)
	, m_Rate(0)
	, m_AutoRegain(false)
{
}

TimeScaler::~TimeScaler()
{
}

void TimeScaler::reset(bool forceReset/* = true*/, TimeScalePriority tsp)
{
	if (!forceReset && (m_CurrPriority > tsp))
		return;

	m_CurrPriority = TimeScalePriority::TSP_Unknown;
	m_CurrScale = 1.f;
	Director::getInstance()->getScheduler()->setTimeScale(m_CurrScale);
}

void TimeScaler::update(float dt)
{
	assert(m_Rate >= 0.f);

	if (m_State != TimeScaleState::Fixed)
	{
		if (m_State == TimeScaleState::SlowDown)
		{
			m_CurrScale -= (m_Rate * (dt / m_CurrScale));
			if (m_CurrScale < m_TargetScale)
			{
				m_CurrScale = m_TargetScale;
				if (m_AutoRegain)
					m_State = TimeScaleState::Regain;
			}
		}
		else if (m_State == TimeScaleState::Regain)
		{
			m_CurrScale += (m_Rate * (dt / m_CurrScale));
			if (m_CurrScale > 1)
				m_CurrScale = 1;
		}
		else
			assert(false);

		Director::getInstance()->getScheduler()->setTimeScale(m_CurrScale);
	}
}

bool TimeScaler::setScale(float t, TimeScalePriority tsp)
{
	if (tsp >= m_CurrPriority)
	{
		m_State = TimeScaleState::Fixed;
		m_CurrScale = t;
		m_CurrPriority = tsp;
		Director::getInstance()->getScheduler()->setTimeScale(m_CurrScale);
		return true;
	}

	return false;
}

bool TimeScaler::setScaling(float targetScale,float originSpendTime, bool autoRegain,TimeScalePriority tsp)
{
	assert(targetScale > 0 && targetScale <= 1.f);

	if (tsp >= m_CurrPriority)
	{
		if (targetScale == m_CurrScale)
			m_State = TimeScaleState::Fixed;
		else if (targetScale > m_CurrScale)
		{
			m_State = TimeScaleState::Regain;
			m_Rate = (targetScale - m_CurrScale) / originSpendTime;
		}
		else
		{
			m_Rate = (m_CurrScale - targetScale) / originSpendTime;
			m_State = TimeScaleState::SlowDown;	//Auto regain
			m_AutoRegain = autoRegain;
		}

		m_TargetScale = targetScale;
		m_CurrPriority = tsp;
		return true;
	}

	return false;
}
