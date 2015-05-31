#ifndef __ENTITY_GROUND_H__
#define __ENTITY_GROUND_H__

#include "Entity.h"

class Ground : public Entity{
CC_CONSTRUCTOR_ACCESS:
	Ground();
	~Ground();
	virtual bool init()override;

public:
	CREATE_FUNC(Ground);

};

#endif