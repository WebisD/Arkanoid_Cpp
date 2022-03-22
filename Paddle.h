#include "BaseEntity.h"
#include "SDL/SDL.h"
#include "Utils.h"

#ifndef _PADDLE_H_
#define _PADDLE_H_

const float defaultPaddleWidth = 100.f;
const float defaultPaddleHeight = 15.f;

class Paddle : public BaseEntity
{
public:
	const float speedFactor = 10;

	Paddle(
		Vector2 position = Vector2::Zero(),
		float height = 15.f,
		float width = defaultPaddleWidth,
		float speed = defaultPaddleHeight,
		Vector2 direction = Vector2::Zero(),
		Vector4 color = Vector4(3, 77, 45, 255)
	);

	void UpdatePaddle(float deltaTime, int windowHeight, int windowWidth);
};

#endif