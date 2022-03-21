#include <iostream>
#include "Game.h"
#include "Block.h"

int* windowWidth, * windowHeight;
Uint32 startTiming, endTiming;
float secondsElapsed = 0.0f;

Game::Game()
	:window(nullptr)
	, renderer(nullptr)
	, ticksCount(0)
	, isRunning(true)
	, firstPlayerScore(0)
	, gameState(GameState::StartScreen)
	, menuBitmapName("menu.bmp")
	, fieldBitmapName("campo.bmp")
	, gameMode(GameMode::SinglePlayer)
{}

bool Game::Initialize()
{
	SDL_Log("Initializing video...");
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

 	SDL_Log("Getting display mode...");
	SDL_DisplayMode displayMode;
	SDL_GetDesktopDisplayMode(0, &displayMode);

	if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0)
	{
		SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
		return false;
	}

	windowWidth = &displayMode.w;
	windowHeight = &displayMode.h;

	*windowWidth = *windowWidth / 2.8f;
	*windowHeight = *windowHeight / 1.2f;

	SDL_Log("Window size: %d x %d", *windowWidth, *windowHeight);

	SDL_Log("Creating window...");
	window = SDL_CreateWindow(
		"Arkanoid",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		*windowWidth,	
		*windowHeight,
		NULL
	);

	if (!window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	SDL_Log("Creating renderer...");
	renderer = SDL_CreateRenderer(
		window, 
		-1,		
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!renderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	screenSurface = SDL_GetWindowSurface(window);

	SDL_Log("Loading background...");
	Game::LoadBackground();

	Game::InitializeVariables();

	return true;
}

bool Game::LoadBitmap(
	std::string bitmapFileName,
	SDL_Surface* surface,
	SDL_Texture* texture,
	SDL_Rect* screenDest,
	SDL_Renderer* renderer
){
	surface = SDL_LoadBMP(bitmapFileName.c_str());

	if (surface == NULL) {
		SDL_Log("Unable to load image %s! SDL Error: %s\n", bitmapFileName.c_str(), SDL_GetError());
		return false;
	}

	int blitResult = SDL_BlitScaled(surface, NULL, screenSurface, screenDest);

	if (blitResult < 0) {
		SDL_Log("Unable to blit image %s onto surface! SDL Error: %s\n", bitmapFileName.c_str(), SDL_GetError());
		return false;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == 0) {
		SDL_Log("Unable to create texture from surface of image %s! SDL Error: %s\n", bitmapFileName.c_str(), SDL_GetError());
		return false;
	}

	return true;
}

void Game::LoadBackground()
{
	SDL_Rect screenDest;
	screenDest.x = 0;
	screenDest.y = 0;
	screenDest.w = *windowWidth;
	screenDest.h = *windowHeight;

	SDL_Log("Loading %s...", menuBitmapName.c_str());
	LoadBitmap(menuBitmapName, menuSurface, menuTexture, &screenDest, renderer);

	SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
	SDL_RenderPresent(renderer);

	SDL_UpdateWindowSurface(window);
}

void Game::RunLoop()
{
	fieldSurface = SDL_LoadBMP("campo.bmp");
	fieldTexture = SDL_CreateTextureFromSurface(renderer, fieldSurface);

	while (isRunning)
	{
		ProcessInput();
		if (gameState != GameState::StartScreen)
		{
			UpdateGame();
			GenerateOutput();
		}
	}
}

void Game::ProcessMenuInput(const Uint8* keyboardState)
{
	if (keyboardState[SDL_SCANCODE_1] || keyboardState[SDL_SCANCODE_KP_1])
	{
		gameMode = GameMode::SinglePlayer;
		gameState = GameState::Playing;
	}
	else if (keyboardState[SDL_SCANCODE_2] || keyboardState[SDL_SCANCODE_KP_2])
	{
		gameMode = GameMode::MultiPlayer;
		gameState = GameState::Playing;
	}
}

void Game::ProcessSingleplayerInput(const Uint8* keyboardState)
{
	firstPaddle.direction.x = 0;

	if (keyboardState[SDL_SCANCODE_A])
	{
		firstPaddle.direction.x -= 1;
	}
	if (keyboardState[SDL_SCANCODE_D])
	{
		firstPaddle.direction.x += 1;
	}
}

void Game::ProcessBotInput(const Uint8* keyboardState)
{
	firstPaddle.direction.y = 0;

	if (keyboardState[SDL_SCANCODE_W])
	{
		firstPaddle.direction.y -= 1;
	}
	if (keyboardState[SDL_SCANCODE_S])
	{
		firstPaddle.direction.y += 1;
	}
}

void Game::ProcessMultiplayerInput(const Uint8* keyboardState)
{
	firstPaddle.direction.y = 0;
	secondPaddle.direction.y = 0;

	if (keyboardState[SDL_SCANCODE_W])
	{
		firstPaddle.direction.y -= 1;
	}
	if (keyboardState[SDL_SCANCODE_S])
	{
		firstPaddle.direction.y += 1;
	}

	if (keyboardState[SDL_SCANCODE_UP])
	{
		secondPaddle.direction.y -= 1;
	}
	if (keyboardState[SDL_SCANCODE_DOWN])
	{
		secondPaddle.direction.y += 1;
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				isRunning = false;
				break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	
	if (state[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}

	if (gameState == GameState::StartScreen) 
	{
		ProcessMenuInput(state);
	}
	else if (gameState == GameState::Playing)
	{
		if (gameMode == GameMode::SinglePlayer)
		{
			ProcessSingleplayerInput(state);
		}
		else if (gameMode == GameMode::MultiPlayer)
		{
			ProcessMultiplayerInput(state);
		}
	}
}

void Game::UpdateScoreBoard(int firstPlayerScore, int secondPlayerScore)
{
	string newTitle = "Jogador 01: " + to_string(firstPlayerScore);

	if (secondPlayerScore != -1) {
		newTitle += " | Jogador 02: " + to_string(secondPlayerScore);
	}

	SDL_SetWindowTitle(window, newTitle.c_str());
}

void Game::InitializeVariables() {
	// paddles
	float paddleWidth = 15.0f;
	float paddleMargin = 30.0f;
	firstPaddle = Paddle(Vector2(*windowWidth / 2.0f, *windowHeight - paddleMargin));
	secondPaddle = Paddle(Vector2(*windowWidth - (paddleMargin + paddleWidth), *windowHeight / 2.0f));

	// initial ball
	balls = vector<Ball>();
	Ball initialBall;
	initialBall.position = Vector2(*windowWidth / 2.f, *windowHeight / 2.f);
	initialBall.velocity = Vector2(-200.f, 500.f);
	balls.push_back(initialBall);
	
	// score
	firstPlayerScore = 0;
	secondPlayerScore = 0;

	// blocks
	int blocksAmount = 73;
	blocks = Block::GenerateBlocks(blocksAmount , *windowWidth);
	
	// SDL
	startTiming = SDL_GetTicks();
	SDL_SetWindowTitle(window, "Arkanoid");
}

void Game::ResetGame() 
{
	gameState = GameState::StartScreen;
	gameMode = GameMode::None;
	InitializeVariables();
	Game::LoadBackground();
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));

	float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;

	if (deltaTime > 0.05f)
		deltaTime = 0.05f;

	ticksCount = SDL_GetTicks();

	endTiming = ticksCount;
	secondsElapsed = (endTiming - startTiming) / 1000.f;

	if (gameMode == GameMode::SinglePlayer) {
		firstPaddle.UpdatePaddle(deltaTime, *windowHeight, *windowWidth);

		for (auto& ball : balls) {
			ball.position.x += ball.velocity.x * ball.speed * deltaTime;
			ball.position.y += ball.velocity.y * ball.speed * deltaTime;

			if (ball.DidCollideWithPaddle(&firstPaddle)) {
				ball.InvertVelocityOnPaddleCollide(&firstPaddle, false);

				if (firstPlayerScore % 3 == 0)
				{
					Vector2 newBallVelocity = Vector2(-200.0f, -ball.velocity.y);
					Ball::AddNewBallToGame(&balls, newBallVelocity, *windowWidth, *windowHeight);
				}
			}

			ball.CheckBallCollisionWithWalls(*windowHeight, *windowWidth);

			for (auto& blocksRow : blocks)
			{
				for (auto& block : blocksRow)
				{
					if (ball.CheckBallCollisionWithBlock(&block))
					{
						Block::RemoveBlock(&blocksRow, &block);
						UpdateScoreBoard(++firstPlayerScore);
						ball.velocity.y *= -1;
					}
				}
			}

			for (auto& collidedBall : balls)
				ball.CheckCollisionWithAnotherBall(&collidedBall);
		}

	}
	else if (gameMode == GameMode::MultiPlayer) {
		Paddle* paddles[] = { &firstPaddle, &secondPaddle };

		for (auto& ball : balls) 
		{
			ball.position.x += ball.velocity.x * ball.speed * deltaTime;
			ball.position.y += ball.velocity.y * ball.speed * deltaTime;

			for (auto& paddle : paddles)
			{
				paddle->UpdatePaddle(deltaTime, *windowWidth, *windowWidth);

				if (ball.DidCollideWithPaddle(paddle))
					ball.InvertVelocityOnPaddleCollide(paddle, true);

				UpdateScoreBoard(firstPlayerScore, secondPlayerScore);

				bool firstPlayerWon = firstPlayerScore > 0 && firstPlayerScore % 3 == 0;
				bool secondPlayerWon = secondPlayerScore > 0 && secondPlayerScore % 3 == 0;

				if (firstPlayerWon || secondPlayerWon)
					ResetGame();
			}

			ball.CheckBallCollisionWithWalls(*windowHeight, *windowWidth);
		}

	}
}

void Game::GenerateOutput()
{
	if (gameMode == GameMode::None) 
		return;

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, fieldTexture, NULL, NULL);

	if (gameMode == GameMode::SinglePlayer) 
		firstPaddle.Draw(renderer);

	else if (gameMode == GameMode::MultiPlayer) 
	{
		firstPaddle.Draw(renderer);
		secondPaddle.Draw(renderer);
	}

	for (auto& blockRow : blocks)
	{
		for (auto& block : blockRow)
		{
			block.Draw(renderer);
		}
	}

	for (auto& ball : balls)
		ball.Draw(renderer);

	SDL_RenderPresent(renderer);
}

Game::~Game()
{
	SDL_FreeSurface(menuSurface);
	SDL_FreeSurface(screenSurface);
	SDL_FreeSurface(fieldSurface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
