#pragma once
#include "Components/Rendering/RenderComponent.h"
#include "Resources/BitmapResource.h"
#include "Math/Vector2.h"

/// 0730 | 작성자 : 이성호
/// 파티클 컴포넌트로 particleInfo를 기준으로 prticleBitmap을 particleCount 만큼 출력한다.
/// Play Reset Pause로 실행 리셋 정지를 할 수 있다.

/// TODO:
/// 최소속도 최대 속도 설정가능해야함
/// 원으로 터지게 변경 -> 이거 해결함 0730
/// 페이드 추가하기

/// <summary>
/// 각 파티클 정보
/// </summary>
struct particleInfo
{
	Vector2 position;	// 이동한 위치 
	Vector2 dirVec;		// 이동 방향
	float speed;		// 이동속도
};

class ParticleRenderer : public RenderComponent
{
public:
	void OnCreate();
	void OnStart();
	void Render(D2DRenderManager* manager);
	void OnDestroy();

	// 플레이 함수
	void Play();
	bool IsPlay();
	void Reset();
	void Pause();

	// 설정 함수
	void SetLoop(bool value);
	bool IsLoop();

	void SetAmount(int value);
	int GetAmount();

	void SetBitmap(std::wstring path);
	ID2D1Bitmap1* GetBitmap();

	void SetMinSpeed(float value);
	float GetMinSpeed();

	void SetMaxSpeed(float value);
	float GetMaxSpeed();

	void SetDuration(float value);
	float GetDuration();

private:
	std::shared_ptr<BitmapResource> particleBitmapResource{};
	std::vector<particleInfo> infos;

	int particleAmount = 100;	// 출력할 파티클 개수
	float minSpeed = 1.0f;		// 최소 속도
	float maxSpeed = 1.0f;		// 최대 속도
				
	float timer = 0.0f;			// duration 확인용 타이머
	float duration = 3.0f;		// 지속시간

	bool isPlay = false;		// 파티클 플레이 여부
	bool isLoop = false;		// 파티클 루프 여부 - 루프하면 자동 Reset()호출
};