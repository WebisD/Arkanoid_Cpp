#pragma once
#include "SinglePlayerStrategy.h"
#include "../../../Game/GameSingleton.h"

void SinglePlayerStrategy::UpdateGame(float deltaTime)
{
	// paddle
	game->firstPaddle->Update(deltaTime);
	game->firstPaddle->CheckWallCollision(game->windowHeight, game->windowWidth);

	// balls
	int scoreToCloneBall = 10;
	for (auto& ball : game->balls)
	{
		if (ball.DidCollideWithPaddle(game->firstPaddle))
			ball.InvertVelocityOnPaddleCollide(game->firstPaddle, false);

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

void SinglePlayerStrategy::GeneratePlayersOutput(SDL_Renderer* renderer)
{
	game->firstPaddle->Draw(renderer);
}

void SinglePlayerStrategy::ProcessInput(const Uint8* keyboardState)
{
	game->firstPaddle->direction.x = 0;

	if (keyboardState[SDL_SCANCODE_A])
		game->firstPaddle->direction.x -= 1;
	
	if (keyboardState[SDL_SCANCODE_D])
		game->firstPaddle->direction.x += 1;
}

void SinglePlayerStrategy::UpdateScoreBoard()
{
	string newTitle = "Jogador 01: " + to_string(game->firstPlayerScore);
	SDL_SetWindowTitle(game->window, newTitle.c_str());
}
