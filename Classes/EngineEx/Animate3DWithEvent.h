#ifndef __ANIMATED3D_WITH_EVENT_H__
#define __ANIMATED3D_WITH_EVENT_H__

#include "cocos2d.h"

USING_NS_CC;

typedef std::function<void()> AnimateCallbackFunc;


        
class Animate3dWithEvent : public Animate3D{

	class AnimEvent{
		public:
			AnimEvent(float time, AnimateCallbackFunc& func):fTriggerTime(time),callBackFunc(func)
			{}

			bool operator<(const AnimEvent& rhs)const{
				return fTriggerTime <= rhs.fTriggerTime;
			}

			float fTriggerTime;					//相对整个Animation的播放进度比例
			AnimateCallbackFunc	callBackFunc;
	};
    
CC_CONSTRUCTOR_ACCESS:
	Animate3dWithEvent();
	virtual ~Animate3dWithEvent();

public:
	static Animate3dWithEvent* create(Animation3D* animation);
	static Animate3dWithEvent* create(Animation3D* animation, float fromTime, float duration);
	static Animate3dWithEvent* createWithFrames(Animation3D* animation, int startFrame, int endFrame, float frameRate = 30.f);

	void	registerEventOnFrame(int eventFrame, AnimateCallbackFunc callbackFunc, float rate = 30.f);
	void	registerEvent(float time, AnimateCallbackFunc callbackFunc);

	virtual void startWithTarget(Node *target) override;
	virtual void update(float t) override;

protected:

	void	checkFrameEvent(float t);

	int							mEventIdx;
	std::vector<AnimEvent>		mFrameEventList;
};

#endif