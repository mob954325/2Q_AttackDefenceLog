#include "RenderSystem.h"
#include "Components/Rendering/RenderComponent.h"
#include "Components/Base/GameObject.h"
#include <algorithm>

RenderSystem::~RenderSystem()
{
	if (!renderComponentGroup.empty())
	{
		renderComponentGroup.clear();
	}
}

void RenderSystem::Register(RenderComponent* comp)
{
	renderComponentGroup[comp->owner->GetRenderLayer()].push_back(comp);
	comp->SetRenderManager(renderManager);
	comp->SetResourceManager(resourceManager);
}

void RenderSystem::UnRegister(RenderComponent* comp)
{
	auto groupIt = renderComponentGroup.find(comp->owner->GetRenderLayer());
	if (groupIt == renderComponentGroup.end()) return;

	auto& comps = groupIt->second;

	auto it = std::find(comps.begin(), comps.end(), comp);
	if (it != comps.end())
	{
		comps.erase(it);
	}
}

void RenderSystem::InitializeRenderLayers()
{
	for (int i = 0; i < EngineData::RenderLayer::LayerCount; i++)
	{
		renderComponentGroup[(EngineData::RenderLayer)i] = std::vector<RenderComponent*>();
	}
}

/// <summary>
/// 컴포넌트 리스트만 제거
/// </summary>
/// <remarks>
/// 각 컴포넌트들은 씬에서 게임오브젝트를 해제할 때 같이 제거되므로 리스트 내용만 제거 되도록 처리
/// </remarks>
void RenderSystem::ClearAll()
{
	renderComponentGroup.clear();
}

void RenderSystem::Update(D2DRenderManager* manager)
{
	assert(manager && "D2DRenderManager is nullptr");

	std::for_each(renderComponentGroup.begin(), renderComponentGroup.end(),
		[](auto& element)
		{
			std::sort(element.second.begin(), element.second.end(), [](RenderComponent* lhs, RenderComponent* rhs)
				{
					return lhs->GetOrderInLayer() < rhs->GetOrderInLayer();
				});
		});

	for (auto group : renderComponentGroup)
	{
		for (auto comp : group.second)
		{
			if (!comp->IsStarted()) continue;

			comp->Render(manager);
		}
	}
}