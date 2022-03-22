#include "GameModeContext.h"

GameModeContext::GameModeContext(GameModeStrategy* strategy)
{
    strategy_ = strategy;
};

void GameModeContext::set_strategy(GameModeStrategy* strategy)
{
    delete this->strategy_;
    this->strategy_ = strategy;
}

void GameModeContext::ProcessInput(const Uint8* keyboardState)
{
    this->strategy_->ProcessInput(keyboardState);
}

void GameModeContext::UpdateGame(float deltaTime)
{
    this->strategy_->UpdateGame(deltaTime);
}

void GameModeContext::UpdateScoreBoard()
{
    this->strategy_->UpdateScoreBoard();
}

void GameModeContext::GeneratePlayersOutput(SDL_Renderer* renderer)
{
    this->strategy_->GeneratePlayersOutput(renderer);
}

GameModeContext::~GameModeContext()
{
    delete this->strategy_;
}