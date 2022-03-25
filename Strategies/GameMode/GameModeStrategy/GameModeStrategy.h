#pragma once

#include <SDL/SDL_render.h>

#ifndef _GAMEMODESTRATEGY_H_
#define _GAMEMODESTRATEGY_H_

class GameModeStrategy
{
    protected:
        class GameSingleton* game;

        GameModeStrategy();
    public:
        virtual void UpdateGame(float deltaTime) = 0;
        virtual void GeneratePlayersOutput(SDL_Renderer* renderer) = 0;
        virtual void ProcessInput(const Uint8* keyboardState) = 0;
        virtual void UpdateScoreBoard() = 0;
        virtual ~GameModeStrategy() {};
};

#endif