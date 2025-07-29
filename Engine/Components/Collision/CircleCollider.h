/// 2025.07.28 | 작성자 : 이성호
/// 원 충돌 체크하는 충돌 컴포넌트
/// 작성 기준 원 vs 원 체크만 있음.

#pragma once
#include "Components/Collision/CollisionComponent.h"
#include "Math/Vector2.h"
#include "Components/Rendering/CircleComponent.h"
class CircleCollider : public CollisionComponent, ICollider
{
public:
	CircleCollider();
	void FixedUpdate(const std::vector<CollisionComponent*>& others, std::vector<CollisionInfo>& outInfos) override;

	ColliderType GetColliderType() override;
	Vector2 GetCenter() const override;

	// 충돌 확인용 인터페이스
	bool CheckCollision(ICollider* other, CollisionInfo& outCollisionInfo) override;
	bool CheckCollisionWithCircle(ICollider* other, CollisionInfo& outCollisionInfo);

	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;
	void SetRadius(float radius);
	float GetRadius() const;

private:
	CircleComponent* debugCircle{};
	float radius = 1.0f; // 지름
	float size = 1.0f;
};