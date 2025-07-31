#pragma once
#include "Utils/Singleton.h"
#include "Components/Rendering/RenderComponent.h"
#include "Datas/EngineData.h"
#include <vector>
#include <map>

class D2DRenderManager;
class BitmapResourceManager;

class RenderSystem : public Singleton<RenderSystem>
{
public:
	friend class Singleton<RenderSystem>;

	void SetD2DRenderManager(D2DRenderManager* pRenderManager) { renderManager = pRenderManager; }
	void SetResourceManager(BitmapResourceManager* pResourceManager) { resourceManager = pResourceManager; }
	void Register(RenderComponent* comp);
	void UnRegister(RenderComponent* comp);

	void InitializeRenderLayers();
	void ClearAll();

	void Update(D2DRenderManager* manager);	// 컴포넌트 업데이트 실행함수
private:
	RenderSystem() = default;
	~RenderSystem();

	D2DRenderManager* renderManager{};
	BitmapResourceManager* resourceManager{};
	std::map<EngineData::RenderLayer, std::vector<RenderComponent*>> renderComponentGroup; // TODO : 컴포넌트별로 순서도 추가
};

// 렌더링 순서 -> EngineData 헤더에 있는 enum 순서대로 렌더링 ( 숫자가 낮을 수록 먼저 렌더링됨 ) 
// Ex> None -> GameObject -> UI