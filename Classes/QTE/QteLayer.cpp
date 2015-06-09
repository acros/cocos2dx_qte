#include "QteLayer.h"
#include "QteHandler.h"

QteLayer::QteLayer() :mHandler(nullptr)
{

}

QteLayer::~QteLayer()
{

}

// bool QteLayer::init()
// {
// 	if (!Layer::init())
// 		return false;
// 
// 	//Load this layer content
// 
// 	return true;
// }

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
