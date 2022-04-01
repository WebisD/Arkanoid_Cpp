#include "../Component/Component.h"
#include "../../Utils/Utils.h"

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#pragma once
class Transform: public Component
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	float width;
	float height;

	virtual void Update(float deltaTime) override;

	Transform(
		Vector3 position = Vector3::Zero(),
		Vector3 rotation = Vector3::Zero(),
		Vector3 scale = Vector3::Zero(),
		float width = 0,
		float height = 0
	) :
		position(position),
		rotation(rotation),
		scale(scale),
		width(width),
		height(height) {};

};

#endif
