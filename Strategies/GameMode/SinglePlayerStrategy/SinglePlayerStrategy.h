#pragma once

#include "../GameModeStrategy/GameModeStrategy.h"

#ifndef _SPSTRATEGY_H_
#define _SPSTRATEGY_H_

class SinglePlayerStrategy : public GameModeStrategy {
	public:
		SinglePlayerStrategy() : GameModeStrategy() {};
		virtual void UpdateGame(float deltaTime);
		virtual void GeneratePlayersOutput(SDL_Renderer* renderer);
		virtual void ProcessInput(const Uint8* keyboardState);
		virtual void UpdateScoreBoard() override;
};

#endif