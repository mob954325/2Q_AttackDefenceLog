#pragma once
#include "Math/Vector2.h"
#include "Datas/CollisionInfo.h"

enum ColliderType
{
	Circle = 0,
	AABB
};

/// <summary>
/// Collider가 공동으로 가지고 있는 인터페이스
/// </summary>
class ICollider
{
public:
	~ICollider() = default;

	virtual ColliderType GetColliderType() = 0;
	virtual Vector2 GetCenter() const = 0;    

	// 충돌 확인용 인터페이스
	virtual bool CheckCollision(ICollider* other, CollisionInfo& outCollisionInfo) = 0;

	// 디버그용 or 렌더링용 AABB 정보
	// virtual Vector2 GetBoundingRect() const = 0;
private:

};