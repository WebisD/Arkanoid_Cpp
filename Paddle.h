#pragma once

#include "SDL/SDL.h"
#include "BaseEntity.h"
#include "Utils.h"

#ifndef _PADDLE_H_
#define _PADDLE_H_

const float defaultPaddleWidth = 100.f;
const float defaultPaddleHeight = 15.f;

class Paddle : public BaseEntity
{
public:
	const float speedFactor = 20;

	Paddle(
		Vector2 position = Vector2::Zero(),
		float height = defaultPaddleHeight,
		float width = defaultPaddleWidth,
		float speed = 15.f,
		Vector2 direction = Vector2::Zero(),
		Vector4 color = Vector4(3, 77, 45, 255)
	);

	virtual void Update(float deltaTime) override;

	void CheckWallCollision(float windowHeight, float windowwIDTH);
};

#endif