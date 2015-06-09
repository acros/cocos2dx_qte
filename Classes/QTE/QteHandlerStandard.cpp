#include "QteHandlerStandard.h"

QteHandlerStandard::QteHandlerStandard(const QteInfo* info) :QteHandler(info)
{

}

QteHandlerStandard::~QteHandlerStandard()
{

}

void QteHandlerStandard::onGuiCallback()
{

	mIsFinished = true;
}
