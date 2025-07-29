#pragma once

#include "Components/Rendering/RenderComponent.h"
#include "Platform/D2DRenderManager.h"
#include "Resources/BitmapResource.h"
#include <deque>

/* 07.29. 한승규
* 트레일 컴포넌트
* 오브젝트에 붙여주면, 그 오브젝트의 좌표가 수치 이하로 변경되면
* 이미지를 박아둠
* 즉, 스탬프를 짧은 간격으로 여러번 찍어서 선을 만드는 컴포넌트임
* 이미지 리소스들을 여러개 만들어야해서 가벼운 구조체로 게임오브젝트를 대체함
*/

struct TrailStamp {
	D2D1_POINT_2F position;
	float angle;
	//float timestamp; // 객체별 생성 시간임, 조건문 돌려서 현재 시각이랑 비교해서 삭제하기 가능
};

class TrailComponent : public RenderComponent
{
public:
	void Update(); // 노드 삭제할때 씀 
	void AddStamp(D2D1_POINT_2F pos);
	void Draw(D2DRenderManager* manager);
	void Render(D2DRenderManager* manager) override; // 이거 기반으로 그려짐
	void SetBitmap(std::wstring path);
	void OnDestroy() override;
	void Clear();

	inline float GetAngle(D2D1_POINT_2F prev, D2D1_POINT_2F current) { // 이전좌표와 현재좌표를 비교해서, 각도(radian) 반환해줌
		return atan2f(current.y - prev.y, current.x - prev.x); // radian
	}

	bool isDraw = false;
	bool wasDraw = false;
	float minDistance = 5.0f; // 최소거리, 즉 스탬프들간의 간격임
	float lifeTime = 0.3f; // 이거일단 사용안함
	int maxTrailCount = 100;

	std::deque<TrailStamp> trails;
	// ID2D1Bitmap1* stampBitmap = nullptr;
	std::shared_ptr<BitmapResource> stampBitmap = nullptr;
};