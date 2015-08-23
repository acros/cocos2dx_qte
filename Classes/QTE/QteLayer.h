#ifndef __QTE_LAYER_H__
#define __QTE_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class QteHandler;

class QteLayer : public Layer{
CC_CONSTRUCTOR_ACCESS:
	QteLayer();
	virtual ~QteLayer();

	virtual void onEnter()override;

	virtual bool onTouchBegan(Touch *touch, Event *unused_event)override;
	virtual void onTouchMoved(Touch *touch, Event *unused_event)override	{}
	virtual void onTouchEnded(Touch *touch, Event *unused_event)override	{}

public:
	void prepare(QteHandler* handler);
	virtual void begin();

protected:
	//Player take action on GUI layer
	virtual void onGuiEvent();



	QteHandler*		mHandler;

};

#endif