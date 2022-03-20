#include "GameSingleton.h";

GameSingleton* GameSingleton::instance = nullptr;

GameSingleton* GameSingleton::GetInstance()
{
    if (!instance)
    {
        instance = new GameSingleton();
    }

    return instance;
}