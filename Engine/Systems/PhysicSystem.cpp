#include "PhysicSystem.h"

void PhysicSystem::Register(PhysicComponent* comp)
{
	components.push_back(comp);
}

void PhysicSystem::UnRegister(PhysicComponent* comp)
{
	auto it = components.begin();

	for (; it != components.end(); it++)
	{
		if (*it == comp)
		{
			components.erase(it);
			break;
		}
	}
}

void PhysicSystem::ClearAll()
{
	components.clear();
}

void PhysicSystem::FixedUpdate(std::vector<CollisionInfo>& collisions)
{
	for (auto comp : components)
	{
		if (!comp->IsStarted()) continue;

		comp->FixedUpdate(collisions);
	}
}

PhysicSystem::~PhysicSystem()
{
	auto it = components.begin();

	for (; it != components.end();)
	{
		it = components.erase(it);
	}

	components.clear();
}
