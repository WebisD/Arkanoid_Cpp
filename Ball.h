#pragma once

#include "BaseEntity.h"
#include "Utils.h"
#include "Paddle.h"
#include "Block.h"

#ifndef _BALL_H_
#define _BALL_H_

class Ball : public BaseEntity
{
public:
	Ball(
		Vector2 position = Vector2::Zero(),
		float width = 15.f,
		float height = 15.f,
		float speed = 1.f,
		Vector2 velocity = Vector2::Zero(),
		Vector2 acceleration = Vector2::Zero(),
		Vector4 color = Vector4(255, 255, 0, 255)
	);

	virtual void Update(float deltaTime) override;

	bool DidCollideWithPaddle(Paddle* paddle);
	void CheckCollisionWithAnotherBall(Ball* ball);
	void InvertVelocityOnPaddleCollide(Paddle* paddle, bool hasToUpdateSpeed);
	void CheckBallCollisionWithWalls(float windowHeight, float windowWidth);
	bool CheckBallCollisionWithBlock(Block* block);
	static void AddNewBallToGame(vector<Ball>* balls, Vector2 velocity, int windowWidth, int windowHeight);
};

#endif