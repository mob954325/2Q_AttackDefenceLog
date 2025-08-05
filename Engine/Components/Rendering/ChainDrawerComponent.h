#pragma once
#include "Components/Rendering/RenderComponent.h"
#include "Platform/D2DRenderManager.h"
#include "Resources/BitmapResource.h"
#include <array>

struct SlicePiece {
	D2D1_RECT_F rect;
	float angle;
	Vector2 pos;
};

class ChainDrawerComponent : public RenderComponent
{
public:
	void Render(D2DRenderManager* manager) override;
	void OnStart() override;

	void Draw(D2DRenderManager* manager);
	void CalcNormalizedRect(float value);
	void SliceRect(std::vector<int> pattern);	

	void SetBitmap(std::wstring path);
	void SetupNodes(Vector2 node, float interval); // 중앙의 노드 좌표와 간격을 넣어주세오

	float duration = 1.0f;
	float piece = 3.0f; // 조각
	bool isPlay = false;

	Vector2 firstNode = { 100, 100 };
	float interval = 1000;

private:
	float timer = 0.0f;

	std::shared_ptr<BitmapResource> baseBitmap;
	std::vector<SlicePiece> pieces;
	std::array<Vector2, 9> positions; // 좌표값들
	D2D1_SIZE_F bmpSize;
};