#pragma once
#include "MultiplayerStrategy.h"
#include "../../../Game/GameSingleton.h"

void MultiplayerStrategy::UpdateGame(float deltaTime)
{
	// paddle
	game->firstPaddle->Update(deltaTime);
	game->firstPaddle->CheckWallCollision(game->windowHeight, game->windowWidth);

	// paddle second
	game->secondPaddle->Update(deltaTime);
	game->secondPaddle->CheckWallCollision(game->windowHeight, game->windowWidth);

	// balls
	int scoreToCloneBall = 10;
	for (auto& ball : game->balls)
	{
		if (ball.DidCollideWithPaddle(game->firstPaddle))
			ball.InvertVelocityOnPaddleCollide(game->firstPaddle, EntitySide::BOTTOM, false);

		if (ball.DidCollideWithPaddle(game->secondPaddle))
			ball.InvertVelocityOnPaddleCollide(game->secondPaddle, EntitySide::TOP, false);

		ball.CheckBallCollisionWithWalls(game->windowHeight, game->windowWidth);

		for (auto& blocksRow : game->blocks)
		{
			for (auto& block : blocksRow)
			{
				if (ball.CheckBallCollisionWithBlock(&block))
				{
					Block::RemoveBlock(&blocksRow, &block);

					if (++game->firstPlayerScore % scoreToCloneBall == 0)
					{
						Vector2 newBallVelocity = Vector2(-200.0f, -ball.velocity.y);
						Ball::AddNewBallToGame(&game->balls, newBallVelocity, game->windowWidth, game->windowHeight);
					}

					/*if (++game->secondPlayerScore % scoreToCloneBall == 0)
					{
						Vector2 newBallVelocity = Vector2(-200.0f, -ball.velocity.y);
						Ball::AddNewBallToGame(&game->balls, newBallVelocity, game->windowWidth, game->windowHeight);
					}*/

					UpdateScoreBoard();

					ball.velocity.y *= -1;
				}
			}

		}

		for (auto& collidedBall : game->balls)
			ball.CheckCollisionWithAnotherBall(&collidedBall);
	}

	// TO DO: verificar pq o update dá erro no for de cima
	for (auto& ball : game->balls) ball.Update(deltaTime);
}

void MultiplayerStrategy::GeneratePlayersOutput(SDL_Renderer* renderer)
{
	game->firstPaddle->Draw(renderer);
	game->secondPaddle->Draw(renderer);
}

void MultiplayerStrategy::ProcessInput(const Uint8* keyboardState)
{
	game->firstPaddle->direction.x = 0;

	if (keyboardState[SDL_SCANCODE_A])
		game->firstPaddle->direction.x -= 1;

	if (keyboardState[SDL_SCANCODE_D])
		game->firstPaddle->direction.x += 1;

	game->secondPaddle->direction.x = 0;

	if (keyboardState[SDL_SCANCODE_LEFT])
		game->secondPaddle->direction.x -= 1;

	if (keyboardState[SDL_SCANCODE_RIGHT])
		game->secondPaddle->direction.x += 1;
}

void MultiplayerStrategy::UpdateScoreBoard()
{
	string newTitle = "Pontos da equipe : " + to_string(game->firstPlayerScore);
	SDL_SetWindowTitle(game->window, newTitle.c_str());
}
