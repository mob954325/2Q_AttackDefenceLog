#pragma once

#include "Components/Rendering/RenderComponent.h"
#include "Platform/D2DRenderManager.h"
#include "Resources/BitmapResource.h"
#include <queue>

/*07.31. 한승규
* 선형보간으로 스탬프 찍는 역할
* 좌표 2개(Vecotr2) 묶여있는(Line) 구조체를 담은 백터를 받은 후
* 백터를 순회하면서 각각의 좌표를 이어줌
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