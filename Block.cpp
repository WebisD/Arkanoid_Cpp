#include "Block.h"
#include <math.h>

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


	SDL_Rect block{
		static_cast<int>(position.x),
		static_cast<int>(position.y),
		static_cast<int>(width),
		static_cast<int>(height)
	};

	/*SDL_Rect block2{
		static_cast<int>(position.x),
		static_cast<int>(position.y),
		static_cast<int>(1),
		static_cast<int>(60)
	};

	SDL_Rect block2{
	static_cast<int>(position.x + width - 0.3),
	static_cast<int>(position.y + height),
	static_cast<int>(1),
	static_cast<int>(60)
	};


	SDL_RenderFillRect(renderer, &block2);
	*/SDL_RenderFillRect(renderer, &block);
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
vector<vector<Block>> Block::GenerateBlocks(int blocksAmount, float windowWidth)
{
	float topMargin = 40.0f;
	
	int blocksByRow = windowWidth / blocksAmount;
	float blockWidth = windowWidth / blocksByRow;
	int numberOfRows = ceil((float)blocksAmount / (float)blocksByRow);
	float gapBetweenBlocks = 1.0f;

	vector<vector<Block>> blocks;

	for (int i = 0; i < numberOfRows; i++)
	{
		vector<Block> row;
		for (int j = 0; j < blocksByRow; j++)
		{
			float rowsAmount = blocks.size();
			float positionX = 0.0f;
			float positionY = rowsAmount * (defaultBlockHeight+ gapBetweenBlocks)*2;

			if (!row.empty())
			{
				Block lastBlock = row.back();
				positionX = lastBlock.position.x + blockWidth + gapBetweenBlocks;
			}

			Block newBlock = Block(Vector2(positionX, positionY), blockWidth);
			row.push_back(newBlock);
		}

		blocks.push_back(row);
	}

	return blocks;
}

