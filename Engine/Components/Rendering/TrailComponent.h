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
	float alpha = 1.0f; // 투명도 + 0.0f 되면 Update에서 제거됨
	bool isActive = true; // 판정이 살아있는지 여부임	
	//float timestamp; // 기능 사용 안함, 나중에 시간비례해서 삭제하고 싶으면, update쪽에서 조건 넣어주면 됨
	//float fadeTimer = 0.0f; // 연출용 타이머
	//static constexpr float fadeDuration = 1.0f; // 사라지는 데 걸리는 시간 (스-테틱이라 한번만 생기지롱) 
};

//==========================================================================

class TrailComponent : public RenderComponent
{
public:
	void Update(); // 노드 삭제 + 플래그 처리용
	void Draw(D2DRenderManager* manager); // 한번 감싼거임, 여기서 for 돌려서 비트맵 찍음
	void Render(D2DRenderManager* manager) override; // 이거 기반으로 그려짐

	void AddStamp(D2D1_POINT_2F pos);
	void Clear(); // 한번에 지우는거임, 큐 비움	

	void SetBitmap(std::wstring path);
	void SetTailBitmap(std::wstring path);
	void SetHeadBitmap(std::wstring path);
	void SetHoldBitmap(std::wstring path);

	void AddHoldStamp();
	
	void OnDestroy() override;	

	inline float GetAngle(D2D1_POINT_2F prev, D2D1_POINT_2F current) {
		return atan2f(current.y - prev.y, current.x - prev.x);
	}

	//==========================================================================
	//플래그가 좀 많음, 델리게이트 쓰면 깔끔해지는데, 일단 직관적으로 이렇게 설계함
	bool isDraw = false; // OnOff용
	bool wasDraw = false; // isDraw를 한번 저장해뒀다가 비교함, 즉 변경지점을 찾는 비교용 버퍼
	
	bool isOutFromBox = true; // 영역밖으로 나가면 true, 뒤에 크기를 자름	

	bool allowHold = true; // 가만히 있으면, hold스탬프 추가할껀지	
	
	bool WasJustReleased() const { return wasDraw && !isDraw; } // 외부에서 상태 확인할때 씀
	bool WasJustPressed() const { return !wasDraw && isDraw; }

	float minDistance = 5.0f;	// 최소거리, 즉 스탬프들간의 간격임 촘촘하면(작으면) 부드러워짐	
	float fadeSpeed = 0.4f;		// 수명 다한 브러쉬의 삭제속도임

	int maxTrailCount = 100;	// 최대 갯수, 찍히는 비트맵의 갯수
	int maxIndex = maxTrailCount / 2; // 투명도 곡선 계산에서 사용됨

	int deleteStepDivider = 10; // 역수임, 1/N 으로 들어가고 삭제 발생시 얼마나 지울지임

	int headIndex = 5; // 큐의 뒤에서 - 시각적으로는 앞에서부터 (범위값임)
	int tailIndex = 5; // 큐의 앞에서 - 시각적으로는 뒤에서부터 (범위값임)
	

	//float lifeTime = 0.3f;		// 이거일단 사용안함, 나중에 update에서 시간 지난거 처리하는식으로 가능함

	std::deque<TrailStamp> cachedTrails; // 이건 저장용임(공개됨) - 신규 갱신은 랜더용으로 사용되는 큐(trails)가 삭제되기전에
	
	bool isNewCached = false; // 외부에서 사용하는 플레그, 받은다음 false 해줘야함
	inline const std::deque<TrailStamp>& CheckingCachedTrails() {
		isNewCached = false;
		return cachedTrails;
	}

private:
	std::deque<TrailStamp> trails; // 큐, 여기에 구조체 담김(좌표, 각도, 수명)
	std::shared_ptr<BitmapResource> stampBitmap = nullptr; // 찍을 비트맵, 브러쉬 넣으면 됨
	std::shared_ptr<BitmapResource> tailBitmap = nullptr;
	std::shared_ptr<BitmapResource> headBitmap = nullptr;
	std::shared_ptr<BitmapResource> holdBitmap = nullptr;

	float holdAlpha = 0.0f;
};