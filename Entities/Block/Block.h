#pragma once

#include <vector>
#include "../BaseEntity/BaseEntity.h"
#include "SDL/SDL.h"
#include "../../Utils/Utils.h"

#ifndef _BLOCK_H_
#define _BLOCK_H_

const float defaultBlockHeight = 16.0f;
const float defaultBlockWidth = 16.0f;

class Block : public BaseEntity
{
public:
	Block(
		Vector2 position = Vector2::Zero(),
		float width = defaultBlockWidth,
		float height = defaultBlockHeight,
		Vector4 color = Vector4(255, 255, 0, 255)
	);

	static vector<vector<Block>> GenerateBlocks(int blocksAmount, int windowWidth);
	static void RemoveBlock(vector<Block>* blocks, Block* blockToRemove);

	virtual void Update(float deltaTime) override {};
};

#endif