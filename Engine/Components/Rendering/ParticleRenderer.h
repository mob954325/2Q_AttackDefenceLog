#pragma once
#include "Components/Rendering/RenderComponent.h"
#include "Resources/BitmapResource.h"
#include "Math/Vector2.h"
#include "Components/Rendering/AnimationRenderer.h"
#include "Components/Rendering/AnimationPlayer.h"

/* 0730 | 작성자 : 이성호
	파티클 컴포넌트로 particleInfo를 기준으로 prticleBitmap을 particleCount 만큼 출력한다.
	Play Reset Pause로 실행 리셋 정지를 할 수 있다. 
*/

/* 07 31 | 작성자 : 이성호
*	추가 내용
		1. 파티클 출력 타입
		2. 최소 - 최대 속도
		3. 애니메이션 등록 함수
		4. 페이드 아웃 시간
*/

/// <summary>
/// 파티클 출력 타입
/// </summary>
enum ParticleShowType
{
	Single = 0,		// 단일 비트맵
	Animation,		// 애니메이션
	RandomSingle	// 시트 위치 중 무작위 출력
};

/// <summary>
/// 각 파티클 정보
/// </summary>
struct ParticleInfo
{
	Vector2 position;	// 이동한 위치 
	Vector2 dirVec;		// 이동 방향
	float speed;		// 이동속도
	int frameIndex = 0;		// 현재 이미지 프레임 인덱스
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
	
	/// <summary>
	/// 루프할지 설정하는 함수
	/// </summary>
	void SetLoop(bool value);

	/// <summary>
	/// 생성할 파티클양을 설정하는 함수
	/// </summary>
	void SetAmount(int value);

	/// <summary>
	/// 출력할 비트맵을 경로로 설정하는 함수 - ParticleShowType::Single에서만 해당 비트맵을 사용함
	/// </summary>
	/// <param name="path"></param>
	void SetBitmap(std::wstring path);
	ID2D1Bitmap1* GetBitmap();

	void SetMinSpeed(float value);
	float GetMinSpeed() const;

	void SetMaxSpeed(float value);
	float GetMaxSpeed() const;

	void SetDuration(float value);
	float GetDuration() const;

	/// <summary>
	/// 출력할 애니메이션 비트맵을 설정하는 함수 - ParticleShowType::Animation, ParticleShowType::RandomSingle에서 사용하는 데이터
	/// </summary>
	/// <param name="sheetPath">스프라이트 시트 경로</param>
	/// <param name="sheetDataPath">스프라이트 시트 json 경로</param>
	/// <param name="clipPath">애니메이션 json 경로</param>
	void SetAnimPlayer(std::wstring sheetPath, std::wstring sheetDataPath, std::wstring clipPath);

	/// <summary>
	/// 파티클 타입 설정 함수
	/// </summary>
	/// <param name="type">Single : 단일 비트맵, Animation : 애니메이션, RandomSingle : 시트의 스프라이트 중 랜덤 한 개 </param>
	void SetShowType(ParticleShowType type);

	void SetFadeOutTime(float value);

	void SetGravity(bool value);
	void SetSeeDirection(bool value);
	void SetDecreasing(bool value);

	AnimationPlayer GetAnimationPlayer();

private:
	std::shared_ptr<BitmapResource> particleBitmapResource{};
	std::vector<ParticleInfo> infos;

	int particleAmount = 100;		// 출력할 파티클 개수
	float minSpeed = 1.0f;			// 최소 속도
	float maxSpeed = 1.0f;			// 최대 속도
	
	float timer = 0.0f;				// duration 확인용 타이머
	float duration = 3.0f;			// 지속시간
	float fadeOutTime = 4.0f;		// 사라지는 시간
	float remainFadeOut = 4.0f;		// 남은 fadeOutTime - 해당 시간으로 capacity 반영
	float decreasingTimer = 3.0f;	// 남은 줄어드는 시간 - 초기화 시 duration 시간 저장
	FLOAT baseScaleX = 1.0f;		// decreasing 계산을 위한 스케일 저장값 x
	FLOAT baseScaleY = 1.0f;		// decreasing 계산을 위한 스케일 저장값 y

	bool isPlay = false;			// 파티클 플레이 여부
	bool isLoop = false;			// 파티클 루프 여부 - 루프하면 자동 Reset()호출
	bool useGravity = false;		// 중력 사용 여부
	bool seeDirection = false;		// 방향으로 바라보기 여부
	bool isDecreasing = false;		// 파티클 줄어 드는거 여부 - Easing 함수의 easeInCubic 사용

	ParticleShowType showType = Single; // 파티클 출력 타입

	AnimationPlayer player; // 파티클이 애니메이션이면 사용

	ComPtr<ID2D1SpriteBatch> spriteBatch;
};