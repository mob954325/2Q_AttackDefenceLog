#include "RenderComponent.h"

void RenderComponent::SetRenderManager(D2DRenderManager* pManager)
{
	renderManager = pManager;
}

void RenderComponent::SetResourceManager(ResourceManager* pManager)
{
	resourceManager = pManager;	
}

void RenderComponent::SetOrderInLayer(int value)
{
	orderInLayer = value;
}

int RenderComponent::GetOrderInLayer()
{
	return orderInLayer;
}
