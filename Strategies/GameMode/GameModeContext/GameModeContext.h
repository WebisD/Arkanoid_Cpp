#pragma once

#include <SDL/SDL_stdinc.h>
#include <SDL/SDL_render.h>
#include "../GameModeStrategy//GameModeStrategy.h"

#ifndef _GAMEMODECTX_H_
#define _GAMEMODECTX_H_

class GameModeContext
{
    public:
        GameModeContext(GameModeStrategy* strategy = nullptr);

        ~GameModeContext();

        void ProcessInput(const Uint8* keyboardState);

        void UpdateGame(float deltaTime);

        void GeneratePlayersOutput(SDL_Renderer* renderer);

        void UpdateScoreBoard();

        void set_strategy(GameModeStrategy* strategy);
    
    private:
        GameModeStrategy* strategy_;
};

#endif