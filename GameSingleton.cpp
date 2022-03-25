#include "GameSingleton.h"

Uint32 startTiming, endTiming;
float secondsElapsed = 0.0f;

GameSingleton* GameSingleton::instance = nullptr;

GameSingleton* GameSingleton::GetInstance()
{
    if (!instance)
        instance = new GameSingleton();

    return instance;
}

bool GameSingleton::Initialize()
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

	windowWidth = displayMode.w / 2.8f;
	windowHeight = displayMode.h / 1.2f;

	SDL_Log("Window size: %d x %d", windowWidth, windowHeight);

	SDL_Log("Creating window...");
	window = SDL_CreateWindow(
		"Arkanoid",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
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
	LoadBackground();
	InitializeVariables();

	return true;
}

bool GameSingleton::LoadBitmap(
	std::string bitmapFileName,
	SDL_Surface* surface,
	SDL_Texture* texture,
	SDL_Rect* screenDest,
	SDL_Renderer* renderer
) {
	surface = SDL_LoadBMP(bitmapFileName.c_str());

	if (surface == NULL)
	{
		SDL_Log("Unable to load image %s! SDL Error: %s\n", bitmapFileName.c_str(), SDL_GetError());
		return false;
	}

	int blitResult = SDL_BlitScaled(surface, NULL, screenSurface, screenDest);

	if (blitResult < 0) 
	{
		SDL_Log("Unable to blit image %s onto surface! SDL Error: %s\n", bitmapFileName.c_str(), SDL_GetError());
		return false;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == 0)
	{
		SDL_Log("Unable to create texture from surface of image %s! SDL Error: %s\n", bitmapFileName.c_str(), SDL_GetError());
		return false;
	}

	return true;
}

void GameSingleton::LoadBackground()
{
	SDL_Rect screenDest;
	screenDest.x = 0;
	screenDest.y = 0;
	screenDest.w = windowWidth;
	screenDest.h = windowHeight;

	SDL_Log("Loading %s...", menuBitmapName.c_str());
	LoadBitmap(menuBitmapName, menuSurface, menuTexture, &screenDest, renderer);

	SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
	SDL_RenderPresent(renderer);

	SDL_UpdateWindowSurface(window);
}

void GameSingleton::RunLoop()
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

void GameSingleton::ProcessMenuInput(const Uint8* keyboardState)
{
	if (keyboardState[SDL_SCANCODE_1] || keyboardState[SDL_SCANCODE_KP_1])
	{
		gameModeCtx = new GameModeContext(new SinglePlayerStrategy());
		gameState = GameState::Playing;
	}
	/*if (keyboardState[SDL_SCANCODE_2] || keyboardState[SDL_SCANCODE_KP_2])
	{
		gameModeCtx = new GameModeContext(new MultiPlayerStrategy());
		gameState = GameState::Playing;
	}*/
}

void GameSingleton::ProcessInput()
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

	// Input Modes
	switch (gameState)
	{
		case GameState::StartScreen:
			ProcessMenuInput(state);
			break;
		case GameState::Playing:
			gameModeCtx->ProcessInput(state);
			break;
	}

	// Close game input
	if (state[SDL_SCANCODE_ESCAPE])
		isRunning = false;
}

void GameSingleton::InitializeVariables() {
	// paddles
	float paddleMargin = 20.0f;
	firstPaddle->position = Vector2(windowWidth / 2.0f, windowHeight - paddleMargin);
	secondPaddle->position = Vector2(windowWidth - (paddleMargin + defaultPaddleWidth), windowHeight / 2.0f);

	// initial ball
	balls = vector<Ball>();
	Ball initialBall;
	initialBall.position = Vector2(windowWidth / 2.f, windowHeight / 2.f);
	initialBall.velocity = Vector2(-200.f, 500.f);
	balls.push_back(initialBall);

	// blocks
	int blocksAmount = 75;
	blocks = Block::GenerateBlocks(blocksAmount, windowWidth);

	// SDL
	startTiming = SDL_GetTicks();
	SDL_SetWindowTitle(window, "Arkanoid");
}

void GameSingleton::ResetGame()
{
	gameState = GameState::StartScreen;
	InitializeVariables();
	GameSingleton::LoadBackground();
}

void GameSingleton::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));

	float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;

	if (deltaTime > 0.05f)
		deltaTime = 0.05f;

	ticksCount = SDL_GetTicks();

	endTiming = ticksCount;
	secondsElapsed = (endTiming - startTiming) / 1000.f;

	gameModeCtx->UpdateGame(deltaTime);
}

void GameSingleton::GenerateOutput()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, fieldTexture, NULL, NULL);

	gameModeCtx->GeneratePlayersOutput(renderer);

	for (auto& ball : balls)
		ball.Draw(renderer);

	for (auto& blockRow : blocks)
	{
		for (auto& block : blockRow)
			block.Draw(renderer);
	}

	SDL_RenderPresent(renderer);
}


void GameSingleton::Shutdown()
{
	delete firstPaddle;
	delete secondPaddle;
	delete gameModeCtx;
	SDL_FreeSurface(menuSurface);
	SDL_FreeSurface(screenSurface);
	SDL_FreeSurface(fieldSurface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
