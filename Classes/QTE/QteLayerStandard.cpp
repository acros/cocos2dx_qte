#include "QteLayerStandard.h"
#include "QteHandler.h"
#include "cocostudio/ActionTimeline/CSLoader.h"
#include "ui/UIHelper.h"

QteLayerStandard::QteLayerStandard()
{

}

QteLayerStandard::~QteLayerStandard()
{

}

bool QteLayerStandard::init()
{
	if (!Layer::init())
		return false;

	//Load this layer content
	auto page = CSLoader::createNode("csb/QTE_Layout.csb");
	addChild(page);
	ui::Helper::doLayout(page);

	mTestBtn = static_cast<ui::Button*>(page->getChildByName("attack"));

	//TODO: DEBUG CODE
	mTestBtn->addClickEventListener(CC_CALLBACK_1(QteLayerStandard::onButtonClick, this));

	return true;
}

void QteLayerStandard::onButtonClick(Ref* ref)
{
	mHandler->onGuiCallback();
}

