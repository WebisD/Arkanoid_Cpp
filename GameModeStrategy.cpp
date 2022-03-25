#include "GameModeStrategy.h"
#include "GameSingleton.h"

GameModeStrategy::GameModeStrategy() 
{
	game = GameSingleton::GetInstance();
}