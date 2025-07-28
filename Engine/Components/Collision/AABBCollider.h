#pragma once
#include "Components/Collision/CollisionComponent.h"
#include "Components/Rendering/BoxComponent.h"
#include "Math/Vector2.h"

/// <summary>
/// owner의 transform의 값을 기준으로 AABB 충돌 판정 컴포넌트
/// </summary>
class AABBCollider : public CollisionComponent, ICollider
{
public:
	AABBCollider();
	void FixedUpdate(const std::vector<CollisionComponent*>& others, std::vector<CollisionInfo>& outInfos) override;

	ColliderType GetColliderType() override;
	Vector2 GetCenter() const override;

	// 충돌 확인용 인터페이스
	bool CheckCollision(ICollider* other, CollisionInfo& outCollisionInfo) override;
	bool CheckCollisionWithAABB(ICollider* other, CollisionInfo& outCollisionInfo);

	void OnCreate() override;
	void OnDestroy() override;
	void SetSize(float width, float height, float size);
	D2D1_RECT_F GetSize() const;

private:
	BoxComponent* debugBoxComponent = nullptr; // 디버깅용

	float width = 0; 
	float height = 0;
	float size = 1.0f;
};