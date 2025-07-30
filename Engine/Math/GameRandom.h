#pragma once
#include "Vector2.h"

/// 25.07.30 | 작성자 : 이성호
/// 랜덤 값 편하게 꺼낼려고 만듦
/// 원 범위 렌덤, 범위 랜덤 등등

static class GameRandom
{
public:
	static float RandomRange(float min, float max);
	static Vector2 RandomInsideUnitCircle();
};

