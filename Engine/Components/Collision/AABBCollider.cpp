#include "AABBCollider.h"
#include "Components/Base/GameObject.h"
#include <algorithm>

AABBCollider::AABBCollider()
{
	collider = this;
	type = ColliderType::AABB;
}

void AABBCollider::FixedUpdate(const std::vector<CollisionComponent*>& others, std::vector<CollisionInfo>& outInfos)
{
	for (auto it = others.begin(); it != others.end(); it++)
	{
		if ((*it)->owner == this->owner) continue;

		ICollider* other = dynamic_cast<ICollider*>((*it)->collider);
		if (other == nullptr) continue;

		CollisionInfo outInfo{ nullptr, nullptr, Vector2::Zero(), 0}; // 충돌 정보
		if (CheckCollision(other, outInfo))
		{
			//std::cout << " [ " << (*it)->owner->GetName() << ", " << this->owner->GetName() << "충돌됨 ] " << std::endl;

			//std::cout << "-- Collision Info -- \n";
			//std::cout << outInfo.a->GetName() << "->" << outInfo.b->GetName() << " : " << outInfo.normal.x << ", " << outInfo.normal.y << "\n";
			//std::cout << "Depth : " << outInfo.penetrationDepth << std::endl;

			outInfos.push_back(outInfo);
		}
	}
}

ColliderType AABBCollider::GetColliderType()
{
	return type;
}

Vector2 AABBCollider::GetCenter() const
{
	return Vector2(owner->GetTransform().GetPosition().x, owner->GetTransform().GetPosition().y);
}

bool AABBCollider::CheckCollision(ICollider* other, CollisionInfo& outCollisionInfo)
{
	ColliderType type = other->GetColliderType();
	switch (type)
	{
	case Circle:
		break;
	case AABB:
		return CheckCollisionWithAABB(other, outCollisionInfo);
	default:
		break;
	}

	return false;
}

bool AABBCollider::CheckCollisionWithAABB(ICollider* other, CollisionInfo& outCollisionInfo)
{
	AABBCollider* otherAABB = static_cast<AABBCollider*>(other);
	if (!otherAABB) return false;

	// AABB 계산
	Vector2 aCenter = GetCenter();
	Vector2 bCenter = otherAABB->GetCenter();
	D2D1_RECT_F aRect = GetSize();
	D2D1_RECT_F bRect = otherAABB->GetSize();

	float aMinX = aCenter.x + aRect.left;
	float aMaxX = aCenter.x + aRect.right;
	float aMinY = aCenter.y + aRect.bottom;
	float aMaxY = aCenter.y + aRect.top;

	float bMinX = bCenter.x + bRect.left;
	float bMaxX = bCenter.x + bRect.right;
	float bMinY = bCenter.y + bRect.bottom;
	float bMaxY = bCenter.y + bRect.top;

	bool isColliding =
		(aMinX < bMaxX) &&
		(aMaxX > bMinX) &&
		(aMinY < bMaxY) &&
		(aMaxY > bMinY);

	// info 데이터 추가
	if (isColliding)
	{
		// 침투한 길이 
		float overlapX = min(aMaxX, bMaxX) - max(aMinX, bMinX);
		float overlapY = min(aMaxY, bMaxY) - max(aMinY, bMinY);

		Vector2 delta = bCenter - aCenter;

		// 침투 깊이가 깊으면 해당 축을 반응 축으로 저장 ( 클수록 덜 겹침 )
		if (overlapX < overlapY)
		{
			outCollisionInfo.normal = (delta.x > 0) ? Vector2(-1, 0) : Vector2(1, 0); // 밀려나야할 법선 벡터
			outCollisionInfo.penetrationDepth = overlapX;
		}
		else // >=
		{
			outCollisionInfo.normal = (delta.y > 0) ? Vector2(0, -1) : Vector2(0, 1);
			outCollisionInfo.penetrationDepth = overlapY;
		}

		outCollisionInfo.a = dynamic_cast<CollisionComponent*>(this);
		outCollisionInfo.b = dynamic_cast<CollisionComponent*>(otherAABB);

		//std::cout << "[Collision] Normal: ("
		//	<< outCollisionInfo.normal.x << ", "
		//	<< outCollisionInfo.normal.y << "), Depth: "
		//	<< outCollisionInfo.penetrationDepth << "\n";
	}

	return isColliding;
}

void AABBCollider::OnCreate()
{
	debugBoxComponent = owner->AddComponent<BoxRenderer>();
	debugBoxComponent->SetRect({ 0,0,0,0 });
}

void AABBCollider::OnStart()
{
	debugBoxComponent->SetOrderInLayer(10);
}

void AABBCollider::OnDestroy()
{
}

void AABBCollider::SetSize(float width, float height, float scale)
{
	this->width = width;
	this->height = height;
	this->size = scale;

	if (!owner->GetTransform().IsUnityCoords())
	{
		debugBoxComponent->SetRect({ -width / 2, -height / 2, width / 2, height / 2 });
	}
	else
	{
		debugBoxComponent->SetRect({ 0, height, width, 0 });
	}

	debugBoxComponent->SetWidth(3.0f);
	debugBoxComponent->SetIsShow(true);
}

D2D1_RECT_F AABBCollider::GetSize() const
{
	D2D1_RECT_F rect{};
	Vector2 centerVec = GetCenter();

	if (owner->GetTransform().IsUnityCoords())
	{
		// 중앙을 기준으로 한 크기 
		rect =
		{
			-width * 0.5f * size,
			height * 0.5f * size,
			width * 0.5f * size,
			-height * 0.5f * size
		};
	}
	else
	{
		// 좌측 상단을 기준으로한 크기
		rect =
		{
			0,
			0,
			width * size,
			height * size
		};
	}

	return rect;
}
