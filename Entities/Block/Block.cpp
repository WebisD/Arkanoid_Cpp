#include <math.h>
#include "Block.h"

Block::Block(Vector2 position, float width, float height, Vector4 color)
{
	this->position = position;
	this->width = width;
	this->height = height;
	this->color = color;
}

vector<vector<Block>> Block::GenerateBlocks(int blocksAmount, int windowWidth)
{
	float topMargin = 80.0f;
	
	int blocksByRow = windowWidth / blocksAmount;
	float blockWidth = windowWidth / blocksByRow;
	int numberOfRows = ceil((float)blocksAmount / (float)blocksByRow);
	float gapBetweenBlocks = 2.0f;

	int computedBlocks = 0;

	vector<vector<Block>> blocks;
	for (int i = 0; i < numberOfRows; i++)
	{
		vector<Block> row;
		for (int j = 0; j < blocksByRow; j++)
		{
			float rowsAmount = blocks.size();
			float positionX = 0.0f;
			float positionY = rowsAmount * (defaultBlockHeight + gapBetweenBlocks);

			if (!row.empty())
			{
				Block lastBlock = row.back();
				positionX = lastBlock.position.x + blockWidth + gapBetweenBlocks;
			}

			Block newBlock = Block(Vector2(positionX, positionY + topMargin), blockWidth);
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
