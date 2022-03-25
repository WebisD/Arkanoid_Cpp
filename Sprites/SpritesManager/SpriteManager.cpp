#include <SDL/SDL_log.h>
#include "SpriteManager.h"

using namespace std;

bool SpriteManager::LoadSprite(
	string bitmapFileName,
	SDL_Surface* screenSurface,
	SDL_Surface* surface,
	SDL_Texture* texture,
	SDL_Rect* screenDest,
	SDL_Renderer* renderer
) {
	surface = SDL_LoadBMP(bitmapFileName.c_str());

	if (surface == NULL)
	{
		SDL_Log("Unable to load sprite %s! SDL Error: %s\n", bitmapFileName.c_str(), SDL_GetError());
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
