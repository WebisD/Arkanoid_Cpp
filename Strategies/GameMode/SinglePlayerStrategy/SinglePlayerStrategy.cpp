#pragma once
#include "SinglePlayerStrategy.h"
#include "../../../Game/GameSingleton.h"

void SinglePlayerStrategy::UpdateGame(float deltaTime)
{

	game->firstPaddle->Update(deltaTime);
	
	for (auto& ball : game->balls) {
		ball.Update(deltaTime);
	}

	for (auto& blocksRow : game->blocks)
	{
		for (auto& block : blocksRow)
		{
			block.Update(deltaTime);
		}
	}
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
