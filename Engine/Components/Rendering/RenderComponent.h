#pragma once
#include "Components/Base/Component.h"

class D2DRenderManager;
class ResourceManager;

class RenderComponent : public Component
{
public:
	RenderComponent() = default;
	virtual ~RenderComponent() = default;

	virtual void Render(D2DRenderManager* manager) = 0;
	void SetRenderManager(D2DRenderManager* pManager);
	void SetResourceManager(ResourceManager* pManager);
	
	void SetOrderInLayer(int value);
	int GetOrderInLayer();

protected:	
	D2DRenderManager* renderManager{};
	ResourceManager* resourceManager{};
	int orderInLayer = 0;
};