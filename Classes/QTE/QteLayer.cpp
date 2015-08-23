#include "QteLayer.h"
#include "QteHandler.h"

QteLayer::QteLayer() :mHandler(nullptr)
{

}

QteLayer::~QteLayer()
{

}

void QteLayer::onGuiEvent()
{
	mHandler->onGuiCallback();
}

void QteLayer::prepare(QteHandler* handler)
{
	mHandler = handler;
}

void QteLayer::begin()
{

}

bool QteLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void QteLayer::onEnter()
{
	Layer::onEnter();
// 
// 	setTouchEnabled(true);
// 	setSwallowsTouches(true);
}

