#include "UISystem.h"

void UISystem::Register(UIComponent* pUIComponent)
{
	components.push_back(pUIComponent);
}

void UISystem::UnRegister(UIComponent* pUIComponent)
{
	auto it = components.begin();
	for (; it != components.end();)
	{
		if (*it == pUIComponent)
		{
			components.erase(it);
			break;
		}

		it++;
	}
}

void UISystem::Update()
{
	for (auto comp : components)
	{
		if (!comp->IsStarted()) continue;

		comp->Update();
	}
}

void UISystem::ClearAll()
{
	components.clear();
}

UISystem::~UISystem()
{
	if (!components.empty())
	{
		ClearAll();
	}
}
