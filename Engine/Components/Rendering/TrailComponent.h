#pragma once

#include "Components/Rendering/RenderComponent.h"
#include "Platform/D2DRenderManager.h"
#include "Resources/BitmapResource.h"
#include <deque>

/* 07.31. 한승규
* 트레일 컴포넌트
* 오너의 트랜스폼을 추적해, 최소거리 이상으로 변동이 생기면, 그자리에 이미지를 박아넣음
* 즉, 수많은 점들이 이어지면서 선이되는 구조
* 이미지 리소스를 많이 사용하다보니, 가벼운 구조체와 큐를 이용해서 랜더함
*/

struct TrailStamp { // 게임오브젝트를 대체하는 구조체, 비트맵 컴포넌트만 요구하기 때문에 가볍게 사용
	D2D1_POINT_2F position; // 좌표
	float angle; // 각도(계산 해야함)
	float timestamp; // 기능 사용 안함, 나중에 시간비례해서 삭제하고 싶으면, update쪽에서 조건 넣어주면 됨
	float alpha = 1.0f; // 투명도 + 0.0f 되면 Update에서 제거됨
	bool isActive = true; // 판정이 살아있는지 여부임	
};

class TrailComponent : public RenderComponent
{
public:
	void Update(); // 노드 삭제 + 플래그 처리용

	void AddStamp(D2D1_POINT_2F pos);
	void Draw(D2DRenderManager* manager); // 한번 감싼거임, 여기서 for 돌려서 비트맵 찍음
	void Render(D2DRenderManager* manager) override; // 이거 기반으로 그려짐
	void SetBitmap(std::wstring path);
	void SetTailBitmap(std::wstring path);
	void OnDestroy() override;
	void Clear(); // 한번에 지우는거임, 큐 비움	

	inline float GetAngle(D2D1_POINT_2F prev, D2D1_POINT_2F current, float prevAngle) { // 이전좌표와 현재좌표를 비교해서, 각도(radian) 반환해줌
		float dx = current.x - prev.x;
		float dy = current.y - prev.y;

		float distSq = dx * dx + dy * dy;
		const float thresholdSq = 25.0f;

		if (distSq < thresholdSq)
			return prevAngle; // 너무 작으면 그냥 기존 각도 유지

		return atan2f(dy, dx); // 제대로 계산
	}

	//플래그가 좀 많음, 델리게이트 쓰면 깔끔해지는데, 일단 직관적으로 이렇게 설계함
	bool isDraw = false; // OnOff용
	bool wasDraw = false; // isDraw를 한번 저장해뒀다가 비교함, 즉 변경지점을 찾는 비교용 버퍼
	bool isOutFromBox = true; // 영역밖으로 나가면 true, 뒤에 크기를 자름
	bool isNewCached = false; // 외부에서 사용하는 플레그, 받은다음 false 해줘야함

	bool isFadingOut = false;

	bool WasJustReleased() const { return wasDraw && !isDraw; } // 외부에서 상태 확인할때 씀
	bool WasJustPressed() const { return !wasDraw && isDraw; }

	float minDistance = 5.0f; // 최소거리, 즉 스탬프들간의 간격임 촘촘하면 부드러워짐
	float lifeTime = 0.3f; // 이거일단 사용안함, 나중에 update에서 시간 지난거 처리하는식으로 가능함
	int maxTrailCount = 100; // 최대 길이, 찍히는 비트맵의 갯수
	float fadeSpeed = 0.7f; // 수명 다한 브러쉬의 삭제속도임

	std::deque<TrailStamp> cachedTrails; // 이건 저장용임(공개됨) - 신규 갱신은 랜더용으로 사용되는 큐(trails)가 삭제되기전에

	// ID2D1Bitmap1* stampBitmap = nullptr;

private:
	std::deque<TrailStamp> trails; // 큐, 여기에 구조체 담김(좌표, 각도, 수명)
	std::shared_ptr<BitmapResource> stampBitmap = nullptr; // 찍을 비트맵, 브러쉬 넣으면 됨
	std::shared_ptr<BitmapResource> tailBitmap = nullptr;
};