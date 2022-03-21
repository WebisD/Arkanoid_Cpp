#include "Ball.h"

Ball::Ball(
	Vector2 position,
	float radius,
	float speed,
	Vector2 velocity,
	Vector2 acceleration,
	Vector4 color
)
	:position(position),
	radius(radius),
	speed(speed),
	velocity(velocity),
	acceleration(acceleration),
	color(color)
{
	topLeft = Vector2(
		position.x,
		position.y
	);

	bottomRight = Vector2(
		position.x + radius,
		position.y + radius
	);
}

void Ball::Draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(
		renderer,
		color.x,
		color.y,
		color.w,
		color.z
	);

	SDL_Rect ball{
		static_cast<int>(position.x),
		static_cast<int>(position.y),
		static_cast<int>(radius),
		static_cast<int>(radius)
	};


	SDL_RenderFillRect(renderer, &ball);
}

bool Ball::DidCollideWithPaddle(Paddle* paddle)
{
	const bool hasCollided = position.x <= paddle->position.x + paddle->width &&
		position.x + radius >= paddle->position.x &&
		position.y <= paddle->position.y + paddle->height &&
		position.y + radius >= paddle->position.y;

	if (hasCollided)
		SDL_Log("Colidiu com raquete");

	return hasCollided;
}

void Ball::InvertVelocityOnPaddleCollide(Paddle* paddle, bool hasToUpdateSpeed)
{
	if (hasToUpdateSpeed)
	{
		speed += 0.01f;
	}

	velocity.x *= -1;
	
	#pragma region vertical collision 
	float topPositionBeforeCollide = (position.y + radius) - velocity.y;
	float bottomPositionBeforeCollide = position.y - velocity.y;

	bool isTopCollision = topPositionBeforeCollide < paddle->position.y;
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

	if (position.x <= ball->position.x + ball->radius &&
		position.x + radius >= ball->position.x &&
		position.y <= ball->position.y + ball->radius &&
		position.y + ball->radius >= ball->position.y
	)
	{
		velocity.x *= -1;
		ball->velocity.x *= -1;

		#pragma region vertical collision 
		float topPositionBeforeCollide = (position.y + radius) - velocity.y;
		float bottomPositionBeforeCollide = position.y - velocity.y;

		bool isTopCollision = topPositionBeforeCollide < ball->position.y;
		bool isBottomCollision = bottomPositionBeforeCollide > ball->position.y + ball->radius;

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
		position.x + radius >= block->position.x &&
		position.y <= block->position.y + block->height &&
		position.y + radius >= block->position.y;
}

void Ball::CheckBallCollisionWithWalls(float windowHeight, float windowWidth)
{
	bool hasCollidedWithBottomWall = position.y + radius >= windowHeight;
	bool hasCollidedWithTopWall = position.y <= 0;

	bool hasCollidedWithRightWall = position.x + radius >= windowWidth;
	bool hasCollidedWithLeftWall = position.x <= 0;

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

