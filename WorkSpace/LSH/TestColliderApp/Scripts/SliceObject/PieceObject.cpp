#include "PieceObject.h"
#include "Components/Base/GameObject.h"
#include "Math/EasingFunction.h"
#include "Utils/GameTime.h"

void PieceObject::OnCreate()
{
	bitmap = owner->AddComponent<BitmapRenderer>();
}

void PieceObject::OnUpdate()
{
	if (isMove && (easingTime <= maxEasingTime))
	{
		float x = EasingList[EasingEffect::InOutQuint](easingTime);
		owner->GetTransform().Translate(moveDir * speed);
		easingTime += Singleton<GameTime>::GetInstance().GetDeltaTime();
	}
}

void PieceObject::SetBitmapByPath(std::wstring path)
{
	bitmap->CreateBitmapResource(path);
}

void PieceObject::SetMoveDirection(const Vector2& vec)
{
	moveDir = vec;
}

void PieceObject::SetSpeed(float value)
{
	speed = value;
}

void PieceObject::Move()
{
	isMove = true;
}

void PieceObject::Reset()
{
	owner->GetTransform().SetPosition(0, 0);
	isMove = false;
	easingTime = 0.0f;
}
