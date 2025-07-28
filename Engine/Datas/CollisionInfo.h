#pragma once
#include "Math/Vector2.h"

class CollisionComponent; // 전방선언

struct CollisionInfo
{
	CollisionComponent* a;
	CollisionComponent* b;
	Vector2 normal; // 충돌한 방향
	float penetrationDepth; // 침투 깊이
};