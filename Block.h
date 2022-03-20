#pragma once
#pragma once

#include "SDL/SDL.h"
#include "Utils.h"
#include "Ball.h"
#include <vector>

using namespace std;

const float defaultBlockHeight = 8.0f;
const float defaultBlockWidth = 16.0f;

class Block
{
public:
	Block(
		Vector2 position = Vector2::Zero(),
		float width = defaultBlockHeight,
		float height = defaultBlockWidth,
		Vector4 color = Vector4(255, 255, 0, 255)
	);
	void Draw(SDL_Renderer* renderer);
	bool DidCollideWithBall(Ball* ball);
	static vector<vector<Block>> GenerateBlocks(int blocksAmount, float windowWidth);

	Vector2 position;
	float width;
	float height;
	Vector4 color;
};
