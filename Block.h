#pragma once
#pragma once

#include "SDL/SDL.h"
#include "Utils.h"
#include "Ball.h"
#include <vector>

class Block
{
public:
	Block(
		Vector2 position = Vector2::Zero(),
		float width = 0.0f,
		float height = 0.0f,
		Vector4 color = Vector4(255, 255, 0, 255)
	);
	void Draw(SDL_Renderer* renderer);
	bool DidCollideWithBall(Ball* ball);
	vector<Block> GenerateBlocks(int blocksAmount, int windowWidth);

	Vector2 position;
	float width;
	float height;
	Vector4 color;
};
