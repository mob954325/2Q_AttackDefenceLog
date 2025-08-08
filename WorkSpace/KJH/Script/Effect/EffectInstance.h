#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Datas/SoundDatas.h"
#include "Components/Logic/InputSystem.h"
#include "Components/Camera/Camera.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Component/EffectComponent.h"
#include "Utils/GameTime.h"
#include "Script/Manager/EffectManager.h"
#include "Components/Rendering/AnimationRenderer.h"
#include "Components/Rendering/AnimationPlayer.h"
#include "Components/UI/Slider.h"
#include "Math/Vector2.h"

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

	void CallEffect(EffectType type , Vector2 info);

	void ParryEffect();
	void GuardEffect();
	void ChargeEffect();
	void HoldEffect();
	void EndEffects();

	float GetValue(size_t type);

private:

	EffectManager* Emanager{};

	float counttime = 0.0f;
	float maxtime = 1.0f;

	float maxtime2 = 3.0f;

	float mydeltatime;

	float PI = 3.141592;

	float chargeValue = 0.0f;
	float CountMathTime = 0.0f;

	float capacapacityWave = 0.0f;

	EffectType effecttype = EffectType::None;

	std::vector<GameObject*> AnimeList;

};


