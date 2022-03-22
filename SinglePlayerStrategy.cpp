#include "GameSingleton.h"
#include "SinglePlayerStrategy.h"

void SinglePlayerStrategy::UpdateGame(float deltaTime)
{
	GameSingleton* game = GameSingleton::GetInstance();

	game->firstPaddle->UpdatePaddle(deltaTime, game->windowHeight, game->windowWidth);

	for (auto& ball : game->balls)
	{
		ball.position.x += ball.velocity.x * ball.speed * deltaTime;
		ball.position.y += ball.velocity.y * ball.speed * deltaTime;

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

					if (++game->firstPlayerScore % 10 == 0)
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

}

void SinglePlayerStrategy::GeneratePlayersOutput(SDL_Renderer* renderer)
{
	GameSingleton* game = GameSingleton::GetInstance();

	game->firstPaddle->Draw(renderer);
}

void SinglePlayerStrategy::ProcessInput(const Uint8* keyboardState)
{
	GameSingleton* game = GameSingleton::GetInstance();

	game->firstPaddle->direction.x = 0;

	if (keyboardState[SDL_SCANCODE_A])
		game->firstPaddle->direction.x -= 1;
	
	if (keyboardState[SDL_SCANCODE_D])
		game->firstPaddle->direction.x += 1;
}

void SinglePlayerStrategy::UpdateScoreBoard()
{
	GameSingleton* game = GameSingleton::GetInstance();

	string newTitle = "Jogador 01: " + to_string(game->firstPlayerScore);
	SDL_SetWindowTitle(game->window, newTitle.c_str());
}
