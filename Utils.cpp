#include "Utils.h"
#include "BaseEntity.h"

Vector2::Vector2(float x, float y) :x(x), y(y) {}

Vector2 Vector2::Zero() {
	return Vector2();
}


Vector3::Vector3(float x, float y, float z) :x(x), y(y), z(z) {}

Vector3 Vector3::Zero() {
	return Vector3();
}


Vector4::Vector4(float x, float y, float w, float z) : x(x), y(y), w(0), z(z) {}

Vector4 Vector4::Zero() {
	return Vector4();
}

float Utils::EuclidianDistance(Vector2 p1, Vector2 p2)
{
	return sqrt(pow(p1.x - p2.x, 2.0f) + pow(p1.y - p2.y, 2.0f));
}

bool Utils::RectangleIntersection(Vector2 tl1, Vector2 br1, Vector2 tl2, Vector2 br2)
{
    if (
        tl1.x == br1.x 
        || tl1.y == br1.y 
        || tl2.x == br2.x
        || tl2.y == br2.y
    ) {
        return false;
    }

    if (tl1.x >= br2.x || tl2.x >= br1.x)
        return false;

    if (br1.y >= tl2.y || br2.y >= tl1.y)
        return false;
        
    return true;
}

int Utils::RandNumber(int min, int max)
{
    srand(time(NULL));
    return rand() % (max - min + 1) + min;
}

bool Utils::CheckCollision(BaseEntity* entity1, BaseEntity* entity2)
{
    return entity1->position.x <= entity2->position.x + entity2->width &&
        entity1->position.x + entity1->width >= entity2->position.x &&
        entity1->position.y <= entity2->position.y + entity2->height &&
        entity1->position.y + entity1->height >= entity2->position.y;
}

EntitySide Utils::GetCollidedSide(BaseEntity* entity1, BaseEntity* entity2)
{
    // vertical
    float bottomPositionBeforeCollide = (entity1->position.y + entity1->height) - entity1->velocity.y;
    float topPositionBeforeCollide = entity1->position.y - entity1->velocity.y;

    bool isTopCollision = topPositionBeforeCollide < entity2->position.y - 0.5;
    bool isBottomCollision = bottomPositionBeforeCollide > entity2->position.y + entity2->height;

    // horizontal
    float leftPositionBeforeCollide = (entity1->position.x + entity1->width) - entity1->velocity.x;
    float rightPositionBeforeCollide = entity1->position.x - entity1->velocity.x;

    bool isLeftCollision = leftPositionBeforeCollide < entity2->position.x - 0.5;
    bool isRightCollision = rightPositionBeforeCollide > entity2->position.x + entity2->width;

    return isTopCollision ? EntitySide::TOP : 
           isBottomCollision ? EntitySide::BOTTOM :
           isLeftCollision ? EntitySide::LEFT :
           isRightCollision ? EntitySide::RIGHT : 
           EntitySide();
}
