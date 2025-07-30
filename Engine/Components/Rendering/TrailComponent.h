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

struct TrailStamp { // 게임오브젝트를 대체하는 구조체, 어차피 비트맵 컴포넌트만 요구하기 때문에 가볍게 사용
	D2D1_POINT_2F position; // 좌표
	float angle; // 각도(계산 해야함)

	float timestamp; // 기능 사용 안함
};

class TrailComponent : public RenderComponent
{
public:
	void Update(); // 노드 삭제 + 플래그 처리용

	void AddStamp(D2D1_POINT_2F pos);
	void Draw(D2DRenderManager* manager); // 한번 감싼거임, 여기서 for 돌려서 비트맵 찍음
	void Render(D2DRenderManager* manager) override; // 이거 기반으로 그려짐
	void SetBitmap(std::wstring path);
	void OnDestroy() override;
	void Clear(); // 한번에 지우는거임, 큐 비움

	inline float GetAngle(D2D1_POINT_2F prev, D2D1_POINT_2F current) { // 이전좌표와 현재좌표를 비교해서, 각도(radian) 반환해줌
		return atan2f(current.y - prev.y, current.x - prev.x); // radian
	}

	bool isDraw = false; // OnOff용
	bool wasDraw = false; // isDraw를 한번 저장해뒀다가 비교함, 즉 변경지점을 찾는 비교용 버퍼
	bool isOutFromBox = true; // 영역밖으로 나가면 true, 뒤에 크기를 자름

	float minDistance = 5.0f; // 최소거리, 즉 스탬프들간의 간격임 촘촘하면 부드러워짐
	float lifeTime = 0.3f; // 이거일단 사용안함, 나중에 update에서 시간 지난거 처리하는식으로 가능함
	int maxTrailCount = 100; // 최대 길이, 찍히는 비트맵의 갯수


	std::deque<TrailStamp> cachedTrails; // 이건 저장용임(공개됨) - 갱신은 삭제되기전에
	// ID2D1Bitmap1* stampBitmap = nullptr;
private:
	std::deque<TrailStamp> trails; // 큐, 여기에 구조체 담김(좌표, 각도, 수명)
	std::shared_ptr<BitmapResource> stampBitmap = nullptr; // 찍을 비트맵, 브러쉬 넣으면 됨
};