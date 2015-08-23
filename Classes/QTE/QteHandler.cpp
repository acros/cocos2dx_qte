#include "QteHandler.h"

QteHandler::QteHandler(const QteInfo* info) 
	: mQteInfo(info)
	, mIsFinished(false)
	, mResult(QTE_Result::QTE_FAILED)
{

}

QteHandler::~QteHandler()
{

}

void QteHandler::update(float dt)
{

}

bool QteHandler::isDone()
{
	return mIsFinished; 
}
