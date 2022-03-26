#pragma once

#include "../BaseEntity/BaseEntity.h"
#include "../Paddle/Paddle.h"
#include "../Block/Block.h"
#include "../../Utils/Utils.h"

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
		Vector4 color = Vector4(
			Utils::RandNumber(100,255), 
			Utils::RandNumber(100, 150), 
			Utils::RandNumber(80, 200),
			Utils::RandNumber(90, 125)
		)
	);

	virtual void Update(float deltaTime) override;

	bool DidCollideWithPaddle(Paddle* paddle);
	void CheckCollisionWithAnotherBall(Ball* ball);
	void InvertVelocityOnPaddleCollide(Paddle* paddle, EntitySide positionPaddle, bool hasToUpdateSpeed);
	void CheckBallCollisionWithWalls(float windowHeight, float windowWidth);
	bool CheckBallCollisionWithBlock(Block* block);
	static void AddNewBallToGame(vector<Ball>* balls, Vector2 velocity, int windowWidth, int windowHeight);
};

#endif