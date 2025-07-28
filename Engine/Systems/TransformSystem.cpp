#include "TransformSystem.h"

void TransformSystem::Register(Transform* pTransform)
{
	components.push_back(pTransform);
}

void TransformSystem::UnRegister(Transform* pTransform)
{
	auto it = components.begin();
	for (; it != components.end();)
	{
		if (*it == pTransform)
		{
			components.erase(it);
			break;
		}

		it++;
	}
}

void TransformSystem::Update()
{	
	for (auto comp : components)
	{
		if (!comp->IsStarted()) continue;

		comp->CalculateFinalMatrix();
	}

	for (auto comp : components)
	{
		if (!comp->IsStarted()) continue;

		comp->ResetDirty();
	}
}

void TransformSystem::ClearAll()
{
	components.clear();	
}

TransformSystem::~TransformSystem()
{
	components.clear();
}
