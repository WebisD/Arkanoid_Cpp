#include "BaseEntity.h"

void BaseEntity::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(
		renderer,
		color.x,
		color.y,
		color.w,
		color.z
	);

	SDL_Rect entity{
		static_cast<int>(position.x),
		static_cast<int>(position.y),
		static_cast<int>(width),
		static_cast<int>(height)
	};

	SDL_RenderFillRect(renderer, &entity);
};
