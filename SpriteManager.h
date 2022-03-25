#pragma once
#include <SDL/SDL_surface.h>
#include <SDL/SDL_render.h>
#include <string>

#ifndef _SPRITEMANAGER_H_
#define _SPRITEMANAGER_H_

class SpriteManager
{
public:
	static bool LoadSprite(std::string bitmapFileName,
		SDL_Surface* screenSurface,
		SDL_Surface* surface,
		SDL_Texture* texture,
		SDL_Rect* screenDest,
		SDL_Renderer* renderer);
};

#endif