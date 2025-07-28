#pragma once
#include "Components/Base/Component.h"
#include "Datas/CollisionInfo.h"

class PhysicComponent : public Component
{
public:
	virtual void FixedUpdate(std::vector<CollisionInfo>& collisions) = 0;
};