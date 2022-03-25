#include "Paddle.h"

Paddle::Paddle(
	Vector2 position,
	float height,
	float width,
	float speed,
	Vector2 direction,
	Vector4 color
)
{
	this->position = position;
	this->height = height;
	this->width = width;
	this->speed = speed;
	this->direction = direction;
	this->color = color;
}

void Paddle::Update(float deltaTime)
{
	if (direction.x != 0)
	{
		position.x += direction.x * speed * speedFactor * deltaTime;
	}
}

void Paddle::CheckWallCollision(float windowHeight, float windowWidth)
{
	if (position.x < 0)
		position.x = 0;

	else if (position.x + width > windowWidth)
		position.x = windowWidth - width;
}