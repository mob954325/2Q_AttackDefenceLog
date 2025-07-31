#pragma once

#include "Components/Rendering/RenderComponent.h"
#include "Platform/D2DRenderManager.h"
#include "Resources/BitmapResource.h"
#include <queue>

/*07.31. 한승규
* 선형보간으로 스탬프 찍는 역할인데
* 좌표 2개 묶여있는 구조체 백터를 받아서
* 스탬프로 선을 그어줌
*/

struct Line {
	Vector2 from;
	Vector2 to;
};

class PatternDrawerComponent : public RenderComponent
{
public:

	void Draw(const std::queue<Line>& lines);
	void Render(D2DRenderManager* manager) override;
	void SetBitmap(std::wstring path);
	void SetLine(std::vector<Line> L) {
		linesToDraw = L;
		timer = 0.0f;
		isPlaying = true;
	}	

	bool isPlaying = false;
private:
	float timer = 0.0f;
	std::vector<Line> linesToDraw;
	std::shared_ptr<BitmapResource> stampBmp = nullptr; // 찍을 비트맵, 브러쉬 넣으면 됨

};