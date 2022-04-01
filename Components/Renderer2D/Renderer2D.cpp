#include "Renderer2D.h"

void Renderer2D::Update(float deltaTime)
{
	SDL_Renderer* renderer = instance->GetRenderer();
	auto object = &find_if(subject->components.begin(), subject->components.end(), any_compare(Transform()));
	Transform* transform = &any_cast<decltype(Transform())>(*object);


	SDL_SetRenderDrawColor(
		renderer,
		color.x,
		color.y,
		color.w,
		color.z
	);

	SDL_Rect entity{
		static_cast<int>(transform->position.x),
		static_cast<int>(transform->position.y),
		static_cast<int>(transform->width),
		static_cast<int>(transform->height)
	};

	SDL_RenderFillRect(renderer, &entity);
}
