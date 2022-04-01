#include "../Component/Component.h"
#include "../../Utils/Utils.h"
#include "../Transform/Transform.h"

#ifndef _INPUT_H_
#define _INPUT_H_

#pragma once
class Input: public Component
{
public:
	virtual void Update(float deltaTime) override;
};

#endif

