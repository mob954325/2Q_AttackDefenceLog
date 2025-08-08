#pragma once
#include "Components/Rendering/RenderComponent.h"
#include "Platform/D2DRenderManager.h"
#include "Resources/BitmapResource.h"
#include "../Engine/Utils/EventDelegate.h"
#include <array>

/* 8.05. 한승규
* 적의 공격 + 플레이어의 공격 가이드라인을 표시해주는 컴포넌트
* 하나의 긴 이미지를, 여러 Rect로 나눠서 연동시켜서 그려주는
* 사실상, 꺾이는 슬라이드 바를 구현함
* vector<int> 넣으면, SetupNodes에서 지정한 좌표를 기반으로 그려줌
* 이미지 길이만큼 나오기 때문에, 이미지를 충분히 길게해주면 좋음
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
	void OnCreate() override;
	
	void Draw(D2DRenderManager* manager);
	void Progress(float value);
	void SliceRect(std::vector<int> pattern);

	void Start(std::vector<int> pattern, float durationTime = 0.0f, std::string ID = " ");

	void SetBitmap(std::wstring path);
	void SetFillBitmap(std::wstring path);
	void SetupNodes(Vector2 node, float interval); // 중앙의 노드 좌표와 간격을 넣어주세오
	
	EventDelegate<const std::string&> OnInterrupted;
	EventDelegate<const std::string&> OnFinished;

	void CancelByID(const std::string& id);


	float piece = 3.0f; // 조각
	bool isPlay = false;

	float progress = 0.0f; // 0 ~1 정규화된 값이 들어가야함

	bool useSlide = false;
	std::string patternID = "";

	// 	Vector2 firstNode = { 100, 100 };
	// 	float interval = 1000;

private:
	float timer = 0.0f;
	float duration = 1.0f; // 외부에서 등록해주는 시간

	float totalLength = 0.0f;



	std::shared_ptr<BitmapResource> baseBitmap;
	std::shared_ptr<BitmapResource> fillBitmap;
	std::vector<SlicePiece> pieces;
	std::array<Vector2, 9> positions; // 좌표값들
	D2D1_SIZE_F bmpSize;
};