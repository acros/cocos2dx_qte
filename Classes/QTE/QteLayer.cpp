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
