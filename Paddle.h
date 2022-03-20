#pragma once
#include "SDL/SDL.h"
#include "Utils.h"

class Paddle
{
public:
	Paddle(
		Vector2 position = Vector2::Zero(),
		float height = 15.0f,
		float width = 80.0f,
		float speed = 300.0f,
		Vector2 direction = Vector2::Zero(),
		Vector4 color = Vector4(3, 77, 45, 255)
	);
	void Draw(SDL_Renderer* renderer);

	void UpdatePaddle(float deltaTime, float windowHeight, float windowWidth);

	Vector2 position;
	float height;
	float width;
	float speed;
	Vector2 direction;

	Vector4 color;

	float speedFactor = 2;

	Vector2 topLeft;
	Vector2 bottomRight;
};
