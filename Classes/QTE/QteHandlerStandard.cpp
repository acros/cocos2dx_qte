#include "QteHandlerStandard.h"

QteHandlerStandard::QteHandlerStandard(const QteInfo* info) :QteHandler(info)
{

}

QteHandlerStandard::~QteHandlerStandard()
{

}

void QteHandlerStandard::onGuiCallback()
{
	mResult = QTE_Result::QTE_SUCCEED;
	mIsFinished = true;
}
