#include "Block.h"

Block::Block(
	Vector2 position,
	float width,
	float height,
	Vector4 color
)
	:position(position),
	width(width),
	height(height),
	color(color)
{
}

void Block::Draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(
		renderer,
		color.x,
		color.y,
		color.w,
		color.z
	);

	SDL_Rect ball{
		static_cast<int>(position.x),
		static_cast<int>(position.y),
		width,
		height
	};


	SDL_RenderFillRect(renderer, &ball);
}

bool Block::DidCollideWithBall(Ball* ball)
{
	const bool hasCollided = position.x <= ball->position.x + ball->radius &&
		position.x + width >= ball->position.x &&
		position.y <= ball->position.y + ball->radius &&
		position.y + height >= ball->position.y;

	if (hasCollided)
		SDL_Log("Bloco colidiu com bola");

	return hasCollided;
}

vector<Block> Block::GenerateBlocks(int blocksAmount, int windowWidth)
{
	float topMargin = 40.0f;

	int blocksAmountByRow = windowWidth / blocksAmount;
	vector<Block> blocks;


	return nullptr;
}

