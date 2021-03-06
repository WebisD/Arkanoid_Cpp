#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Vector2 
{
public:
	Vector2(float x = .0f, float y = .0f);
	static Vector2 Zero();

	float x;
	float y;
};

class Vector3 
{
public:
	Vector3(float x = .0f, float y = .0f, float z = .0f);
	static Vector3 Zero();

	float x;
	float y;
	float z;
};

class Vector4 
{
public:
	Vector4(float x = .0f, float y = .0f, float w = .0f, float z = .0f);
	static Vector4 Zero();

	float x;
	float y;
	float w;
	float z;
};

class Utils 
{
public:
	static float EuclidianDistance(Vector2 p1, Vector2 p2);
	static bool RectangleIntersection(Vector2 tl1, Vector2 br1, Vector2 tl2, Vector2 br2);
	static int RandNumber(int min, int max);
	static bool CheckCollision(class BaseEntity* entity1, class BaseEntity* entity2);
	static enum class EntitySide GetCollidedSide(class BaseEntity* entity1, class BaseEntity* entity2);
};