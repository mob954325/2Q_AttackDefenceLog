#pragma once
#include "Utils/Singleton.h"
#include "Components/Physics/PhysicComponent.h"
#include "Datas/CollisionInfo.h"

class PhysicSystem : public Singleton<PhysicSystem>
{
public:
	friend class Singleton<PhysicSystem>;

	void Register(PhysicComponent* comp);
	void UnRegister(PhysicComponent* comp);
	void ClearAll();

	void FixedUpdate(std::vector<CollisionInfo>& collisions);
private:
	PhysicSystem() = default;
	~PhysicSystem();

	std::vector<PhysicComponent*> components;
};