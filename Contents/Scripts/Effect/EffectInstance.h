#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Datas/SoundDatas.h"
#include "Components/Logic/InputSystem.h"
#include "Components/Camera/Camera.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "EffectComponent.h"
#include "Utils/GameTime.h"
#include "EffectManager.h"
#include "Components/Rendering/AnimationRenderer.h"
#include "Components/Rendering/AnimationPlayer.h"
#include "Components/UI/Slider.h"
#include "Math/Vector2.h"
#include <vector>

/*
미리 풀링으로 만들어둔 이펙트, 파티클들
*/

enum class EffectType
{
	None,
	ParryEffect,
	GuardEffect,
	ChargeEffect,
	HoldEffect
};

class EffectInstance : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;

	void CallEffect(EffectType type , const Vector2& info);

	void ParryEffect();
	void GuardEffect();
	void ChargeEffect();
	void HoldEffect();
	void EndEffects();
	
	//8.09 추가
	void DoParry(int n);	
	void DoGuard(int n);

	void SetAnimePosition(const std::vector<Vector2>& vectorList);

	float GetValue(size_t type);

	void CallAnime(size_t num);

	void StopAnime(size_t num);

	void StopAllAnime();
private:
	std::vector<Vector2> nodePos; // 좌표 9개 기억 + 0 ~ 8

	EffectManager* Emanager{};

	float counttime = 0.0f;
	float maxtime = 1.0f;

	float maxtime2 = 3.0f; // 차징시간

	float mydeltatime;

	float PI = 3.141592;

	float chargeValue = 0.0f;
	float CountMathTime = 0.0f;

	float capacapacityWave = 0.0f;

	EffectType effecttype = EffectType::None;

	std::vector<GameObject*> AnimeList;

	size_t AnimeNum = 0;
	bool CheckPlayAnime = false;
	float Animeduration = 0.33333334f;
	float AnimeCount = 0.0f;
	/*float Animeduration = 0.0f;*/

	//각 애니메이션을 관리하기위한 struct
	struct AnimeState {
		bool   playing = false;
		float  t = 0.0f;        // 경과 시간
		float  duration = 0.0f; // 슬롯별 지속시간
	};

	//그것을 담는 백터
	std::vector<AnimeState>  AnimeStates;
};


