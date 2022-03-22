#include "SDL/SDL.h"
#include "Utils.h"

#ifndef _BASEENTITY_H_
#define _BASEENTITY_H_

class BaseEntity
{
public:
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	Vector4 color;
	Vector2 direction;
	float width;
	float height;
	float speed;

	void Draw(SDL_Renderer* renderer);
};

#endif