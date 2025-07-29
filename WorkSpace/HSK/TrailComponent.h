#pragma once

#include "Components/Rendering/RenderComponent.h"

/* 07.29. 한승규
* 트레일 컴포넌트
* 오브젝트에 붙여주면, 그 오브젝트의 좌표를 일정 시간(혹은 길이)동안 저장해둠
*
*/

struct TrailStamp {
	D2D1_POINT_2F position;
	float angle;
	float timestamp; // 객체별 생성 시간임, 조건문 돌려서 현재 시각이랑 비교해서 삭제하기 가능
};

class TrailComponent : public RenderComponent
{
public:
	void Update(float currentTime); // 시간처리할때만 씀

	void AddStamp(D2D1_POINT_2F pos, float angle, float time);
	void Draw(ID2D1RenderTarget* rt);
	void Render(D2DRenderManager* manager) override; // 이거 기반으로 그려짐

	inline float GetAngle(D2D1_POINT_2F prev, D2D1_POINT_2F current) { // 이전좌표와 현재좌표를 비교해서, 각도(radian) 반환해줌
		return atan2f(current.y - prev.y, current.x - prev.x); // radian
	}

	float minDistance = 10.0f; // 최소거리, 즉 스탬프들간의 간격임
	float lifeTime = 0.3f;
	
private:
	std::deque<TrailStamp> trails{};
	ID2D1Bitmap* stampBitmap = nullptr;
};