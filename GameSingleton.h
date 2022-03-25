#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "GameModeContext.h"
#include "SinglePlayerStrategy.h"

enum class GameState { StartScreen, Playing };

class GameSingleton
{
    public:
        static GameSingleton* GetInstance();

		Paddle* firstPaddle;
		Paddle* secondPaddle;
		vector<Ball> balls;
		vector<vector<Block>> blocks;
		
		int firstPlayerScore, secondPlayerScore;
		
		SDL_Window* window;
		int windowHeight;
		int windowWidth;
		
		bool Initialize();
		void LoadBackground();
		void RunLoop();
		void Shutdown();

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
			menuBitmapName("arkanoid.bmp"),
			fieldBitmapName("campo.bmp"),
			firstPaddle(new Paddle()),
			secondPaddle(new Paddle()),
			gameModeCtx(nullptr)
		{};

		void ProcessInput();
		void UpdateGame();
		void GenerateOutput();
		void ProcessMenuInput(const Uint8* keyboardState);
		void ResetGame();
		void InitializeVariables();
		bool LoadBitmap(
			std::string bitmapFileName,
			SDL_Surface* surface,
			SDL_Texture* texture,
			SDL_Rect* screenDest,
			SDL_Renderer* renderer
		);
		
		//surfaces
		SDL_Surface* screenSurface = nullptr;
		SDL_Surface* menuSurface = nullptr;
		SDL_Texture* menuTexture = nullptr;

		SDL_Surface* fieldSurface = nullptr;
		SDL_Texture* fieldTexture = nullptr;

		// render
		SDL_Renderer* renderer = nullptr;
		Uint32 ticksCount;

		// Assets
		std::string menuBitmapName;
		std::string fieldBitmapName;
	};