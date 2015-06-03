#ifndef __QTE_LAYER_H__
#define __QTE_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class QteHandler;

class QteLayer : public Layer{
CC_CONSTRUCTOR_ACCESS:
	QteLayer(QteHandler* handler);
	virtual ~QteLayer();

	virtual bool init()override;

public:


protected:
	//Player take action on GUI layer
	virtual void onGuiEvent();



	QteHandler*		mHandler;

};

#endif