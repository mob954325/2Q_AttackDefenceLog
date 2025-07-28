#include "CollisionComponent.h"
#include "Components/Base/GameObject.h"

void CollisionComponent::SetTrigger(bool value)
{
	isTrigger = value;
}

bool CollisionComponent::IsTrigger()
{
	return isTrigger;
}
