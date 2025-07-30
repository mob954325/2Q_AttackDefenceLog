#include "CircleCollider.h"
#include "Components/Base/GameObject.h"
#include <algorithm>

CircleCollider::CircleCollider()
{
	collider = this;
	type = ColliderType::Circle;
}

void CircleCollider::FixedUpdate(const std::vector<CollisionComponent*>& others, std::vector<CollisionInfo>& outInfos)
{
	for (auto it = others.begin(); it != others.end(); it++)
	{
		if ((*it)->owner == this->owner) continue;

		ICollider* other = dynamic_cast<ICollider*>((*it)->collider);
		if (other == nullptr) continue;

		CollisionInfo outInfo{ nullptr, nullptr, Vector2::Zero(), 0 }; // 충돌 정보
		if (CheckCollision(other, outInfo))
		{
			outInfos.push_back(outInfo);
		}
	}
}

ColliderType CircleCollider::GetColliderType()
{
	return type;
}

Vector2 CircleCollider::GetCenter() const
{
	return Vector2(owner->GetTransform().GetPosition().x, owner->GetTransform().GetPosition().y);
}

bool CircleCollider::CheckCollision(ICollider* other, CollisionInfo& outCollisionInfo)
{
	ColliderType type = other->GetColliderType();
	switch (type)
	{
	case Circle:
		return CheckCollisionWithCircle(other, outCollisionInfo);
	case AABB:
		break;
	default:
		break;
	}

	return false;
}

bool CircleCollider::CheckCollisionWithCircle(ICollider* other, CollisionInfo& outCollisionInfo)
{
	CircleCollider* otherCircle = static_cast<CircleCollider*>(other);
	if (!otherCircle) return false;

	float aRadius = GetRadius();
	float bRadius = otherCircle->GetRadius();

	Vector2 aCenter = GetCenter();
	Vector2 bCenter = otherCircle->GetCenter();

	bool isColliding = (bCenter.x - aCenter.x) * (bCenter.x - aCenter.x) + (bCenter.y - aCenter.y) * (bCenter.y - aCenter.y) <= (aRadius + bRadius) * (aRadius + bRadius);

	if (isColliding)
	{
		// 침투한 길이 

		Vector2 delta = bCenter - aCenter;

		outCollisionInfo.normal = (aCenter - bCenter).Normalize();
		outCollisionInfo.penetrationDepth = 1; // 임시 

		outCollisionInfo.a = dynamic_cast<CollisionComponent*>(this);
		outCollisionInfo.b = dynamic_cast<CollisionComponent*>(otherCircle);

		//std::cout << "[Collision] Normal: ("
		//	<< outCollisionInfo.normal.x << ", "
		//	<< outCollisionInfo.normal.y << "), Depth: "
		//	<< outCollisionInfo.penetrationDepth << "\n";
	}

	return isColliding;
}

void CircleCollider::OnCreate()
{

}

void CircleCollider::OnStart()
{
	debugCircle = owner->AddComponent<CircleRenderer>();
	debugCircle->SetRadius(radius);	
}

void CircleCollider::OnDestroy()
{
}

void CircleCollider::SetRadius(float radius)
{
	this->radius = radius;
	if (debugCircle)
	{
		debugCircle->SetRadius(radius);
	}
}

float CircleCollider::GetRadius() const
{
	return radius;
}