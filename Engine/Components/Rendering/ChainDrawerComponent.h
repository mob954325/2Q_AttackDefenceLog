#pragma once
#include "Components/Rendering/RenderComponent.h"
#include "Platform/D2DRenderManager.h"
#include "Resources/BitmapResource.h"
#include <array>

/* 8.05. 한승규
* 적의 공격 + 플레이어의 공격 가이드라인을 표시해주는 컴포넌트
*  + 주석추가 예정
*/

struct SlicePiece {
	D2D1_RECT_F rect;
	float angle;
	Vector2 pos;
	float length; // 각 조각의 길이
	float fillAmount;
	float alpha;
};

class ChainDrawerComponent : public RenderComponent
{
public:
	void Render(D2DRenderManager* manager) override;
	void OnStart() override;

	void Draw(D2DRenderManager* manager);
	void Progress(float value);
	void SliceRect(std::vector<int> pattern);

	void SetBitmap(std::wstring path);
	void SetFillBitmap(std::wstring path);
	void SetupNodes(Vector2 node, float interval); // 중앙의 노드 좌표와 간격을 넣어주세오

	float duration = 1.0f;
	float piece = 3.0f; // 조각
	bool isPlay = false;

	Vector2 firstNode = { 100, 100 };
	float interval = 1000;

private:
	float timer = 0.0f;
	float totalLength = 0.0f;

	std::shared_ptr<BitmapResource> baseBitmap;
	std::shared_ptr<BitmapResource> fillBitmap;
	std::vector<SlicePiece> pieces;
	std::array<Vector2, 9> positions; // 좌표값들
	D2D1_SIZE_F bmpSize;
};