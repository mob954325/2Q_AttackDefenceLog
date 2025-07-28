#include "MonoBehaviorSystem.h"
#include "Components/Base/GameObject.h"

void MonoBehaviorSystem::Register(MonoBehavior* comp)
{
	pendingComponents.push_back(comp);
}

void MonoBehaviorSystem::UnRegister(MonoBehavior* comp)
{
	for (auto it = components.begin(); it != components.end(); it++)
	{
		if (*it == comp)
		{
			components.erase(it);
			break;
		}
	}
}

void MonoBehaviorSystem::ClearAll()
{
	components.clear();
}

void MonoBehaviorSystem::Update()
{
	for (MonoBehavior* mono : components)
	{
		if (mono->IsActiveSelf())
		{
			mono->OnUpdate();
		}
	}
}

void MonoBehaviorSystem::FixedUpdate()
{
	for (MonoBehavior* mono : components)
	{
		if (mono->IsActiveSelf())
		{
			mono->OnFixedUpdate();
		}
	}
}

void MonoBehaviorSystem::ProcessPendingComponents()
{
	components.insert(components.end(), pendingComponents.begin(), pendingComponents.end());
	pendingComponents.clear();
}

MonoBehaviorSystem::~MonoBehaviorSystem()
{
	if (!components.empty())
	{
		ClearAll();
	}
}	
