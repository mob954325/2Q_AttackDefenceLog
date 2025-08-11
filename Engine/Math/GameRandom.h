#pragma once
#include "Vector2.h"

/// 25.07.30 | 작성자 : 이성호
/// 랜덤 값 편하게 꺼낼려고 만듦
/// 원 범위 렌덤, 범위 랜덤 등등

static class GameRandom
{
public:
	/// <summary>
	/// min 이상 max 미만의 float형 숫자를 랜덤으로 추출하는 함수
	/// </summary>
	/// <param name="min">최소 값</param>
	/// <param name="max">최대 값</param>
	/// <returns>[min, max) 구간 값</returns>
	static float RandomRange(float min, float max);

	/// <summary>
	/// 원점이 0,0일 때의 반지름이 1인 원에 랜덤으로 좌표값을 찍는 함수
	/// </summary>
	/// <returns>x와 y값이 (-1, 1)인 값</returns>
	static Vector2 RandomInsideUnitCircle();
};

