#include <math.h>
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

	SDL_Rect block{
		static_cast<int>(position.x),
		static_cast<int>(position.y),
		static_cast<int>(width),
		static_cast<int>(height)
	};

	SDL_RenderFillRect(renderer, &block);
}

vector<vector<Block>> Block::GenerateBlocks(int blocksAmount, float windowWidth)
{
	float topMargin = 80.0f;
	
	int blocksByRow = windowWidth / blocksAmount;
	float blockWidth = windowWidth / blocksByRow;
	int numberOfRows = ceil((float)blocksAmount / (float)blocksByRow);
	float gapBetweenBlocks = 1.0f;

	int computedBlocks = 0;

	vector<vector<Block>> blocks;
	for (int i = 0; i < numberOfRows; i++)
	{
		vector<Block> row;
		for (int j = 0; j < blocksByRow; j++)
		{
			float rowsAmount = blocks.size();
			float positionX = 0.0f;
			float positionY = topMargin + rowsAmount * (defaultBlockHeight + gapBetweenBlocks) *2;

			if (!row.empty())
			{
				Block lastBlock = row.back();
				positionX = lastBlock.position.x + blockWidth + gapBetweenBlocks;
			}

			Block newBlock = Block(Vector2(positionX, positionY), blockWidth);
			row.push_back(newBlock);

			if (++computedBlocks >= blocksAmount) break;
		}

		blocks.push_back(row);
	}

	return blocks;
}

void Block::RemoveBlock(vector<Block>* blocks, Block* blockToRemove)
{
	int it = 0;
	for(auto& block : *blocks)
	{
		if (&block == blockToRemove)
			blocks->erase(blocks->begin() + it);
		it++;
	}
}

