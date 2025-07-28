#pragma once
#include "Components/Base/Component.h"
#include "Components/Collision/ICollider.h"
#include "Datas/CollisionInfo.h"

class CollisionComponent : public Component
{
public:
	virtual void FixedUpdate(const std::vector<CollisionComponent*>& others, std::vector<CollisionInfo>& outInfos) = 0;

	void SetTrigger(bool value);
	bool IsTrigger();

	ICollider* collider = nullptr; // 인터페이스 주입하기

protected:
	ColliderType type;

private:
	bool isTrigger = false;
};