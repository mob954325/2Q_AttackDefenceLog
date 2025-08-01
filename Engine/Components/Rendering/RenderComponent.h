#pragma once
#include "Components/Base/ActiveComponent.h"

class D2DRenderManager;
class BitmapResourceManager;

class RenderComponent : public ActiveComponent
{
public:
	RenderComponent() = default;
	virtual ~RenderComponent() = default;

	virtual void Render(D2DRenderManager* manager) = 0;
	void SetRenderManager(D2DRenderManager* pManager);
	void SetResourceManager(BitmapResourceManager* pManager);
	
	void SetOrderInLayer(int value);
	int GetOrderInLayer();

protected:	
	D2DRenderManager* renderManager{};
	BitmapResourceManager* resourceManager{};
	int orderInLayer = 0; // 이거 어디서 작동되는지 확인하기
};