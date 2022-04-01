#include "../Component/Component.h"
#include "../../Utils/Utils.h"
#include "SDL/SDL.h"
#include "../../Entities/BaseEntity/BaseEntity.h"
#include "../Transform/Transform.h"

#ifndef _RENDERER2D_H_
#define _RENDERER2D_H_

using namespace std;

#pragma once
class Renderer2D: public Component
{
public:
	
	Vector4 color;

	virtual void Update(float deltaTime) override;
};

#endif

