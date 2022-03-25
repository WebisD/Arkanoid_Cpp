#include "GameModeStrategy.h"
#include "../../../Game/GameSingleton.h"

GameModeStrategy::GameModeStrategy() 
{
	game = GameSingleton::GetInstance();
}