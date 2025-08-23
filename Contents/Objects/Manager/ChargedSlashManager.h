#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "../Engine/Utils/EventDelegate.h"
#include "../Engine/Components/Logic/InputSystem.h"
#include "../Contents/Scripts/Effect/EffectInstance.h"
#include "../Contents/Scripts/Effect/Finaleffect.h"

/* 8.11. 한승규
* 차징과 슬레쉬를 구현한 매니저
* 특정 좌표 >> 1, 3, 7, 9의 노드 중 하나에 차징 판정이 생기고
* 해당 좌표에서 마우스 좌클릭을 누른 상태로 기다리면 차징됨
*
* 차징이 충분히 된 상태에서
* 정해진 방향으로 마우스를 움직여 좌클릭을 놓게되면
*
* 놓게된 시점의 좌표를 기준으로
* 방향백터를 검사해서, 방향에 맞게 그었는지 판정 + 시간안에 그었는지 판정
*
* 만약 판정이 성공적이라면, 베틀매니저 쪽으로 성공했다고 알림
* 배틀 매니저 내부에서, 시간 측정할꺼임.
*
* 혹시라도 시간이 초과된다면, 배틀매니저 내부에서 Cancel호출을 알려줄꺼임(델리게이트)
*
* + 이펙트도 넣어주긴 할꺼임
*/

constexpr float PI = 3.14159265358979323846f; // 이 얼마나 아름다운 숫자인가

struct SlashCache {
	Vector2 pos; // 위치벡터
	Vector2 normal; // 방향벡터
};

class ChargedSlashManager : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;

	//=========================================================
	// 외부에서 호출해줄꺼

	void SetUpNodePos(const std::vector<Vector2>& vec); // 노드 9개의 좌표 등록

	void Start(int n); //외부에서 이거 불러주면 시작함 << 델리게이트로 외부에서 뭐시기임
	void Cancel(); // 다 집어치우라는 의미임 << 델리게이트로 외부에서 호출해줄 함수임

	float chargeTimeRequired = 3.0f; // 차징 요구 시간
	float allowedAngleRadians = 0.8660f; // 15도 허용
	float exitTimeRequired = 1.0f; // 이탈 이후, 마우스를 놓는데까지 걸리는 요구시간
	float minDist = 100.0f; // 최소 거리	

	//=========================================================
	void Reset(); // 내부에서 판정이 실패인 경우, 다시 처음부터 시켜주는 함수

	EventDelegate<> onChargeStart; // 외부에 있는 오브젝트(노드)를 비활성화 해주기 위한 델리게이트 
	EventDelegate<> onFinisherSuccess; // 내부에서 판정에 성공했다는걸 알려주는 델리게이트 - 베틀매니저 내부에 있는 함수와 연결해줄 생각	

	bool isHide = true; // 숨었찌롱
	bool isMoveDone = false; // 다 옮김? 이라는 플래그
	float filterDuration = 2.0f; // 2초동안 페이드 인 - 아웃함
	void HideOrRevealFilter(float dt); // 필터 움직여주는 함수, 업데이트에서 돌림


protected:	
	bool soundFlag = true;

	EffectInstance* eff;
	Finaleffect* fff; // FinaleFFect

	float radius = 50.0f; //차징 범위
	float timer = 0.0f; // 타이머(측정용)	
	float mouseTimer = 0.0f;

	float filterTimer = 0.0f; //필터 연출용 타이머
	bool isPlay = false;

	InputSystem* inputSys; // 쓰기 편하게 빼둠
	BitmapRenderer* bitmapRenderer; // 마찬가지

	//BitmapRenderer* aa; // 마찬가지
	BitmapRenderer* pressDotInfo;
	BitmapRenderer* slashLineInfo;
//	BitmapRenderer* cc; // 마찬가지

	D2D1_SIZE_F size;

	std::vector<GameObject*> filter; // 필터 4개
	std::vector<D2D1_SIZE_F> filterSizes; // 몰라 이거로 저장해두자, 매번 꺼내쓰는거 귀찮음
			
	bool isUpperRight = false; // 기본이미지가 오른쪽 위를 기준으로 대각선이 갈림
	bool isUpperLeft = false; //그래서 이건 뒤집어줘야함 + 좌표값을 이미지 크기의 -한거로 해줘야함

private:
	Vector2 nowNormalVec = { 0,0 };
	Vector2 nowPos = { 0,0 };
	Vector2 centerPos;

	bool isInside = false; // 마우스가 차징범위 내부에 있는지를 판단하는 플래그
	bool isCharged = false; // 차징 조건을 충족했는지

	float progress = 0.0f; // 0 ~ 1 정규화 값	
	
	//=========================================================
	// [전제] 마우스가 좌클릭이 눌린 상태로, 차징 범위안에 올라갔다
	bool CheckMouseInside();

	// [판정 1] 차징 - 원 안에 얼마나 머물렀는가, 충분히 머물렀다면 차징성공
	//void Charging();

	// [판?정] 최소 거리 이상 + 이탈 타이머 확인 + 방향벡터 확인
	bool isSuccess(Vector2 pos, float t);

	// [판정 2] 마우스 좌클릭 놓은 위치 + 시간 충족 여부 확인
	// 놓은 위치는 항상 4번(중앙)노드를 기준으로 방향 백터를 생성함, 1 -> 5 혹은 9 -> 5 처럼
	void Slashing(Vector2 pos, float time);

	//=========================================================
	
	std::vector<SlashCache> slashCache;
	
	inline float clampf(float v, float minVal, float maxVal) { // 나만의 작은 클램프 함수 C++14를 고집하는 자의 의지
		return (v < minVal) ? minVal : (v > maxVal ? maxVal : v);
	}
};


