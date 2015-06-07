#include "QteLayer.h"
#include "QteHandler.h"

QteLayer::QteLayer(QteHandler* handler) : mHandler(handler)
{

}

QteLayer::~QteLayer()
{

}

bool QteLayer::init()
{
	if (!Layer::init())
		return false;

	//Load this layer content

	return true;
}

void QteLayer::onGuiEvent()
{
	mHandler->onGuiCallback();
}
