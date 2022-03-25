#include "Ball.h"
#include "Utils.h"
#include <iostream>

Ball::Ball(
	Vector2 position,
	float width,
	float height,
	float speed,
	Vector2 velocity,
	Vector2 acceleration,
	Vector4 color
)
{
	this->position = position;
	this->speed = speed;
	this->width = width;
	this->height = height;
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->color = color;
}

void Ball::InvertVelocityOnPaddleCollide(Paddle* paddle, bool hasToUpdateSpeed)
{
	if (hasToUpdateSpeed) speed += 0.01f;
	
	EntitySide collidedSide = Utils::GetCollidedSide(this, paddle);

	if (collidedSide == EntitySide::TOP || collidedSide == EntitySide::BOTTOM)
		velocity.y *= -1;
	else
		velocity.x *= -1;
}

void Ball::CheckCollisionWithAnotherBall(Ball* ball)
{
	if (this == ball) return;

	if (Utils::CheckCollision(this, ball))
	{
		velocity.x *= -1;
		ball->velocity.x *= -1;
		
		EntitySide collidedSide = Utils::GetCollidedSide(this, ball);

		if (collidedSide == EntitySide::TOP || collidedSide == EntitySide::BOTTOM)
		{
			velocity.y *= -1;
			ball->velocity.y *= -1;
		}
	}
}

bool Ball::DidCollideWithPaddle(Paddle* paddle)
{
	return Utils::CheckCollision(this, paddle);
}

bool Ball::CheckBallCollisionWithBlock(Block* block)
{
	return Utils::CheckCollision(this, block);
}

void Ball::CheckBallCollisionWithWalls(float windowHeight, float windowWidth)
{
	bool hasCollidedWithBottomWall = position.y + height >= windowHeight;
	bool hasCollidedWithTopWall = position.y <= 0.5;

	bool hasCollidedWithRightWall = position.x + width >= windowWidth;
	bool hasCollidedWithLeftWall = position.x <= 0.5;

	if (hasCollidedWithTopWall || hasCollidedWithBottomWall)
		velocity.y *= -1;

	if (hasCollidedWithLeftWall || hasCollidedWithRightWall)
		velocity.x *= -1;
}

void Ball::AddNewBallToGame(vector<Ball>* balls, Vector2 velocity, int windowWidth, int windowHeight)
{
	Ball newBall;

	int randomNumber = Utils::RandNumber(2, 7);

	newBall.position = Vector2(
		windowWidth / 2 + windowWidth / randomNumber,
		windowHeight / 2 + windowHeight / randomNumber
	);

	newBall.velocity = velocity;

	balls->push_back(newBall);
}

void Ball::Update(float deltaTime)
{
	position.x += velocity.x * speed * deltaTime;
	position.y += velocity.y * speed * deltaTime;
}

