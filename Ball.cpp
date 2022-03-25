#include "Ball.h"

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

bool Ball::DidCollideWithPaddle(Paddle* paddle)
{
	const bool hasCollided = position.x <= paddle->position.x + paddle->width &&
		position.x + width >= paddle->position.x &&
		position.y <= paddle->position.y + paddle->height &&
		position.y + height >= paddle->position.y;

	if (hasCollided)
		SDL_Log("Colidiu com raquete");

	return hasCollided;
}

void Ball::InvertVelocityOnPaddleCollide(Paddle* paddle, bool hasToUpdateSpeed)
{
	if (hasToUpdateSpeed)
		speed += 0.01f;

	#pragma region vertical collision 
	float topPositionBeforeCollide = (position.y + height) - velocity.y;
	float bottomPositionBeforeCollide = position.y - velocity.y;

	bool isTopCollision = topPositionBeforeCollide < paddle->position.y - 0.3;
	bool isBottomCollision = bottomPositionBeforeCollide > paddle->position.y + paddle->height;

	if (isTopCollision || isBottomCollision)
	{
		velocity.y *= -1;
	}
# pragma endregion 
}

void Ball::CheckCollisionWithAnotherBall(Ball* ball)
{
	if (ball == this) return; // prevents compare a ball with itself

	if (position.x <= ball->position.x + ball->width &&
		position.x + width >= ball->position.x &&
		position.y <= ball->position.y + ball->height &&
		position.y + ball->height >= ball->position.y
		)
	{
		velocity.x *= -1;
		ball->velocity.x *= -1;

		#pragma region vertical collision 
		float topPositionBeforeCollide = (position.y + height) - velocity.y;
		float bottomPositionBeforeCollide = position.y - velocity.y;

		bool isTopCollision = bottomPositionBeforeCollide < ball->position.y;
		bool isBottomCollision = topPositionBeforeCollide > ball->position.y + ball->height;

		if (isTopCollision || isBottomCollision)
		{
			velocity.y *= -1;
			ball->velocity.y *= -1;
		}
		# pragma endregion 
	}
}


bool Ball::CheckBallCollisionWithBlock(Block* block)
{
	return position.x <= block->position.x + block->width &&
		position.x + width >= block->position.x &&
		position.y <= block->position.y + block->height &&
		position.y + height >= block->position.y;
}

void Ball::CheckBallCollisionWithWalls(float windowHeight, float windowWidth)
{
	bool hasCollidedWithBottomWall = position.y + height >= windowHeight - 0.5;
	bool hasCollidedWithTopWall = position.y <= 0.5;

	bool hasCollidedWithRightWall = position.x + width >= windowWidth - 0.5;
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