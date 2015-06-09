#ifndef __QTE_HANDLER_STANDARD_H__
#define __QTE_HANDLER_STANDARD_H__

#include "QteHandler.h"

class QteHandlerStandard : public QteHandler
{
CC_CONSTRUCTOR_ACCESS:
	QteHandlerStandard(const QteInfo* info);
	~QteHandlerStandard();

public:
	CREATE_FUNC_QTE_HANDLER(QteHandlerStandard,QteInfo);


	virtual void onGuiCallback()override;

};

#endif