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
};

class ParticleRenderer : public RenderComponent
{
public:
	void OnCreate();
	void OnStart();
	void Render(D2DRenderManager* manager);
	void OnDestroy();

	void Play();
	void Reset();
	void Pause();
	void SetLoop(bool value);
	void SetBitmap(std::wstring path);

private:
	std::shared_ptr<BitmapResource> particleBitmap{};
	std::vector<particleInfo> infos;

	int particleCount = 100;
	float speed = 1.0f;

	float timer = 0.0f;
	float duration = 3.0f;

	bool isPlay = false;
	bool isLoop = false;
};