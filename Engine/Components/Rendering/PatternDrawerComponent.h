#pragma once

#include "Components/Rendering/RenderComponent.h"
#include "Platform/D2DRenderManager.h"
#include "Resources/BitmapResource.h"
#include <queue>

/*07.31. 한승규
* 선형보간으로 스탬프 찍는 역할(TrailComponent의 기능을 분리해서 가져온거임)
* 좌표 2개(Vecotr2) 묶여있는(Line) 구조체를 담은 백터를 받은 후
* 백터를 순회하면서 각각의 좌표를 이어줌
*/

struct Line { // 사실 Vector2 하나만 있어도 되긴 하는데, 이후에 변경(뭐 방향성이 추가되는?)을 대비해서 두개로 놔둠, 솔직히 좀 낭비긴 함
	Vector2 from;
	Vector2 to;
};

class PatternDrawerComponent : public RenderComponent
{
public:	
	void Render(D2DRenderManager* manager) override;
	void SetBitmap(std::wstring path);
	inline void SetLine(std::vector<Line> L) {
		linesToDraw = L;
		timer = 0.0f;
		isPlaying = true;
	}	

	bool isPlaying = false;
	float duration = 1.0f; // 듀-레이션, 초 단위
	float minDistance = 10.0f; // 얼마나 촘촘하게 할껀지임, 낮으면 더 부드러워짐

private:
	float timer = 0.0f;
	std::vector<Line> linesToDraw;
	std::shared_ptr<BitmapResource> stampBmp = nullptr; // 찍을 비트맵, 브러쉬 넣으면 됨
};