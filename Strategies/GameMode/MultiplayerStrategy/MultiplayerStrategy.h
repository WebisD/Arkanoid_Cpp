#pragma once

#include "../GameModeStrategy/GameModeStrategy.h"

#ifndef _MPSTRATEGY_H_
#define _MPSTRATEGY_H_

class MultiplayerStrategy : public GameModeStrategy {
public:
	MultiplayerStrategy() : GameModeStrategy() {};
	virtual void UpdateGame(float deltaTime);
	virtual void GeneratePlayersOutput(SDL_Renderer* renderer);
	virtual void ProcessInput(const Uint8* keyboardState);
	virtual void UpdateScoreBoard() override;
};

#endif
