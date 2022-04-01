#pragma once

#include "../Entities/Paddle/Paddle.h"
#include "../Entities/Ball/Ball.h"
#include "../Entities/Block/Block.h"
#include "../Strategies/GameMode/GameModeContext/GameModeContext.h"

#ifndef _GAMESINGLETON_
#define _GAMESINGLETON_

enum class GameState { StartScreen, Playing };

class GameSingleton
{
    public:
        static GameSingleton* GetInstance();

		Paddle* firstPaddle;
		Paddle* secondPaddle;
		int firstPlayerScore, secondPlayerScore;

		vector<Ball> balls;
		vector<vector<Block>> blocks;
		
		SDL_Window* window;
		float windowHeight, windowWidth;
		
		bool Initialize();
		void RunLoop();
		void Shutdown();

		SDL_Renderer* GetRenderer();

	private:
		static GameSingleton* instance;
		
		bool isRunning;
		
		GameState gameState;
		GameModeContext* gameModeCtx;

		GameSingleton() : 
			window(nullptr),
			renderer(nullptr),
			ticksCount(0),
			isRunning(true),
			firstPlayerScore(0),
			secondPlayerScore(0),
			windowHeight(0),
			windowWidth(0),
			gameState(GameState::StartScreen),
			firstPaddle(new Paddle()),
			secondPaddle(new Paddle()),
			gameModeCtx(nullptr)
		{};

		void InitializeEntities();
		
		void LoadBackground();

		void UpdateGame();
		void ResetGame();

		void ProcessInput();
		void ProcessMenuInput(const Uint8* keyboardState);
		
		void GenerateOutput();
		
		//surfaces
		SDL_Surface* screenSurface = nullptr;
		SDL_Surface* menuSurface = nullptr;
		SDL_Texture* menuTexture = nullptr;

		SDL_Surface* galaxySurface = nullptr;
		SDL_Texture* galaxyTexture = nullptr;

		// render
		SDL_Renderer* renderer = nullptr;
		Uint32 ticksCount;

		// background assets
		string menuSpriteFileName = "Sprites/Assets/arkanoid.bmp";
		string galaxySpriteFileName = "Sprites/Assets/galaxy.bmp";
	};

#endif