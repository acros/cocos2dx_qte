#ifndef __QTE_LAYER_STANDARD_H__
#define __QTE_LAYER_STANDARD_H__

#include "QteLayer.h"
#include "cocos2d.h"
#include "ui/UIButton.h"

USING_NS_CC;

class QteLayerStandard : public QteLayer
{
CC_CONSTRUCTOR_ACCESS:
	QteLayerStandard();
	virtual ~QteLayerStandard();

	virtual bool init()override;

public:
	CREATE_FUNC(QteLayerStandard);


protected:
	void onButtonClick(Ref* ref);


	RefPtr<ui::Button>	mTestBtn;

};

#endif