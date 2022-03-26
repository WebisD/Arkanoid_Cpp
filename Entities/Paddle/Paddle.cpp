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
	for (auto& component : components)
	{
		component.Update();
	}
}