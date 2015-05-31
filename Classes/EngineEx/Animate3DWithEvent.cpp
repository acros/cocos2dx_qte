#include "Animate3DWithEvent.h"


Animate3dWithEvent::Animate3dWithEvent()
{

}

Animate3dWithEvent::~Animate3dWithEvent()
{

}

Animate3dWithEvent* Animate3dWithEvent::create(Animation3D* animation)
{
	auto animate = new (std::nothrow) Animate3dWithEvent();
	animate->_animation = animation;
	animation->retain();

	animate->autorelease();
	animate->setDuration(animation->getDuration());
	animate->setOriginInterval(animation->getDuration());

	return animate;
}

Animate3dWithEvent* Animate3dWithEvent::create(Animation3D* animation, float fromTime, float duration)
{
	auto animate = Animate3dWithEvent::create(animation);

	float fullDuration = animation->getDuration();
	if (duration > fullDuration - fromTime)
		duration = fullDuration - fromTime;

	animate->_start = fromTime / fullDuration;
	animate->_last = duration / fullDuration;
	animate->setDuration(duration);
	animate->setOriginInterval(duration);

	return  animate;
}

Animate3dWithEvent* Animate3dWithEvent::createWithFrames(Animation3D* animation, int startFrame, int endFrame, float frameRate /*= 30.f*/)
{
	float perFrameTime = 1.f / frameRate;
	float fromTime = startFrame * perFrameTime;
	float duration = (endFrame - startFrame) * perFrameTime;

	auto animate = create(animation, fromTime, duration);
	return  animate;
}

void Animate3dWithEvent::registerEventOnFrame(int eventFrame, AnimateCallbackFunc callbackFunc, float rate /*= 30.f*/)
{
	float perFrameTime = 1.f / rate;
	float triggerTime = eventFrame * perFrameTime;
	float triggerTimePer = triggerTime / _animation->getDuration();

	assert(triggerTimePer >= 0.f && triggerTimePer <= 1.f);

	mFrameEventList.push_back(AnimEvent(triggerTimePer, callbackFunc));

    std::sort(mFrameEventList.begin(), mFrameEventList.end());
}

void Animate3dWithEvent::registerEvent(float time, AnimateCallbackFunc callbackFunc)
{
	float percentageOfAnim = _start + time / _duration;

	if (percentageOfAnim > 1.f)
		percentageOfAnim = 1.f;
	else if (percentageOfAnim < 0.f)
		percentageOfAnim = 0.f;

	assert(percentageOfAnim >= 0.f && percentageOfAnim <= 1.f);

	mFrameEventList.push_back(AnimEvent(percentageOfAnim, callbackFunc));

	std::sort(mFrameEventList.begin(),mFrameEventList.end());
}

void Animate3dWithEvent::startWithTarget(Node *target)
{
	Animate3D::startWithTarget(target);

	//Reset the frame event flag
	if (_playReverse)
		mEventIdx = mFrameEventList.size() - 1;
	else
		mEventIdx = 0;
}

void Animate3dWithEvent::update(float t)
{
	if (_target)
	{
		if (_state == Animate3D::Animate3DState::FadeIn && _lastTime > 0.f)
		{
			_accTransTime += (t - _lastTime) * getDuration();

			_weight = _accTransTime / _transTime;
			if (_weight >= 1.0f)
			{
				_accTransTime = _transTime;
				_weight = 1.0f;
				_state = Animate3D::Animate3DState::Running;
				Sprite3D* sprite = static_cast<Sprite3D*>(_target);
				s_fadeInAnimates.erase(sprite);
				s_runningAnimates[sprite] = this;
			}
		}
		else if (_state == Animate3D::Animate3DState::FadeOut && _lastTime > 0.f)
		{
			_accTransTime += (t - _lastTime) * getDuration();

			_weight = 1 - _accTransTime / _transTime;
			if (_weight <= 0.0f)
			{
				_accTransTime = _transTime;
				_weight = 0.0f;

				Sprite3D* sprite = static_cast<Sprite3D*>(_target);
				s_fadeOutAnimates.erase(sprite);
			}
		}
		_lastTime = t;

		if (_weight > 0.0f)
		{
			float transDst[3], rotDst[4], scaleDst[3];
			float* trans = nullptr, *rot = nullptr, *scale = nullptr;
			if (_playReverse)
				t = 1 - t;

			t = _start + t * _last;

			checkFrameEvent(t);

			for (const auto& it : _boneCurves) {
				auto bone = it.first;
				auto curve = it.second;
				if (curve->translateCurve)
				{
					curve->translateCurve->evaluate(t, transDst, EvaluateType::INT_LINEAR);
					trans = &transDst[0];
				}
				if (curve->rotCurve)
				{
					curve->rotCurve->evaluate(t, rotDst, EvaluateType::INT_QUAT_SLERP);
					rot = &rotDst[0];
				}
				if (curve->scaleCurve)
				{
					curve->scaleCurve->evaluate(t, scaleDst, EvaluateType::INT_LINEAR);
					scale = &scaleDst[0];
				}
				bone->setAnimationValue(trans, rot, scale, this, _weight);
			}
		}
	}
}

void Animate3dWithEvent::checkFrameEvent(float t)
{
	if (_playReverse)
	{
		//Test this!
		assert(false);
		for (; mEventIdx >= 0;)
		{
			if (mFrameEventList[mEventIdx].fTriggerTime >= t)
				mFrameEventList[mEventIdx--].callBackFunc();
			else
				break;
		}
	}
	else
	{
		for (; mEventIdx < mFrameEventList.size();)
		{
			if (mFrameEventList[mEventIdx].fTriggerTime <= t)
				mFrameEventList[mEventIdx++].callBackFunc();
			else 
				break;
		}
	}

}
