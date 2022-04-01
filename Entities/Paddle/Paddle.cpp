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

	components.push_back(Transform(
		Vector3(position.x, position.y, 0),
		Vector3::Zero(),
		Vector3::Zero(),
		width,
		height
	));

	components.push_back(Renderer2D());

	components.push_back(Input());
}

void Paddle::Update(float deltaTime)
{
	for (auto& component : components)
	{
		component.Update(deltaTime);
	}
}