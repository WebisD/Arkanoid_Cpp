/*
Antonio Gustavo Muniz		            RA: 22.119.001-0
Gabriel Bueno Vila Real de Oliveira		RA: 22.119.077-0
Henrique Vital de Carvalho	            RA: 22.119.078-8
João Vitor Dias dos Santos	            RA: 22.119.006-9
Weverson Pereira da Silva	            RA: 22.119.004-4
*/

#include "GameSingleton.h"

int main(int argc, char** argv)
{
	GameSingleton* game = GameSingleton::GetInstance();

	bool success = game->Initialize();

	if (success)
	{
		game->RunLoop();
	}

	game->Shutdown();

	return 0;
}
