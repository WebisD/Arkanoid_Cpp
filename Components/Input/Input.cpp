#include "Input.h"


void Input::Update(float deltaTime)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	subject->direction.x = 0;

	if (state[SDL_SCANCODE_A])
		subject->direction.x -= 1;

	if (state[SDL_SCANCODE_D])
		subject->direction.x += 1;
}