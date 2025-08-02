#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Math/Vector2.h"
#include "Components/Rendering/BitmapRenderer.h"

class PieceObject : public MonoBehavior
{
public:
	void OnCreate();
	void OnUpdate();

	void SetBitmapByPath(std::wstring path);
	void SetMoveDirection(const Vector2& vec);
	void SetSpeed(float value);

	/// <summary>
	/// moveDir * speed로 움직이는 함수
	/// </summary>
	void Move();
	void Reset();

private:
	BitmapRenderer* bitmap{};
	Vector2 moveDir{};	// 움직일 위치 벡터
	float speed = 0.3f;
	float easingTime = 0.0f;
	float maxEasingTime = 1.0f;
	bool isMove = false;
};

