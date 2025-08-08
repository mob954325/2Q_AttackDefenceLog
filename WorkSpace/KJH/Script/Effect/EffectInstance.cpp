#include "EffectInstance.h"
#include "Components/Base/GameObject.h"
#include <iostream>
#include "Systems/AudioSystem.h"
#include "Components/Camera/CameraManager.h"
#include "Scene/SceneManager.h"
#include "Math/EasingFunction.h"
#include <cmath>


//Update로 프레임마다 이펙트들 업데이트
void EffectInstance::OnUpdate()
{
	if (effecttype == EffectType::None) return;
	counttime += Singleton<GameTime>::GetInstance().GetDeltaTime();
	
	switch (effecttype)
	{
	case EffectType::ParryEffect:
		ParryEffect();
		break;

	case EffectType::GuardEffect:
		GuardEffect();
		break;

	case EffectType::ChargeEffect:
		ChargeEffect();
		break;
	case EffectType::HoldEffect:
		HoldEffect();
		break;
	}
}

//변수 초기화 및 Emanager 등록
void EffectInstance::OnCreate()
{
	counttime = 0;
	Emanager = owner->AddComponent<EffectManager>();
}

//초기 이미시 셋팅 및  파티클 수치 설정
void EffectInstance::OnStart()
{
	Emanager->CreateEffectObject(7);
	Emanager->CreateParticleObject(2);
	//패리
	Emanager->SetEffectImage(0, L"../../Resource/Particles/circle_outer.png");
	Emanager->SetEffectImage(1, L"../../Resource/Particles/circle_inner.png");
	Emanager->SetEffectImage(2, L"../../Resource/Particles/line_horizon.png");
	//방어
	Emanager->SetEffectImage(3, L"../../Resource/Particles/defend/circle_inner.png");
	Emanager->SetEffectImage(4, L"../../Resource/Particles/defend/horizon_line.png");
	Emanager->SetEffectImage(5, L"../../Resource/Particles/nomal/combo_node_outer_circle.png");
	Emanager->SetEffectImage(6, L"../../Resource/Particles/nomal/combo_node_inner_circle.png");



	Emanager->SetLayer(0, 30);
	Emanager->SetLayer(1, 31);
	Emanager->SetLayer(2, 32);
	Emanager->SetLayer(3, 33);
	Emanager->SetLayer(4, 34);
	Emanager->SetLayer(5, 35);
	Emanager->SetLayer(6, 35);



	Emanager->GetParticleComponent(0)->SetOrderInLayer(35);
	Emanager->GetParticleComponent(0)->SetLoop(false);
	Emanager->GetParticleComponent(0)->SetMinSpeed(1.3f);
	Emanager->GetParticleComponent(0)->SetMaxSpeed(1.5f);
	Emanager->GetParticleComponent(0)->SetDuration(0.8f);
	Emanager->GetParticleComponent(0)->SetFadeOutTime(0.7f);
	Emanager->GetParticleComponent(0)->SetAmount(50);
	Emanager->GetParticleComponent(0)->SetAnimPlayer(L"../../Resource/Particles/SparkSheet.png",
		L"../../Resource/Json/SparkSheet/SparkSheet_sprites.json",
		L"../../Resource/Json/SparkSheet/Red_Spark_anim.json");
	Emanager->GetParticleComponent(0)->SetShowType(ParticleShowType::RandomSingle);
	Emanager->GetParticleComponent(0)->SetGravity(false);
	Emanager->GetParticleComponent(0)->SetSeeDirection(true);
	Emanager->GetParticleComponent(0)->SetDecreasing(true);

	Emanager->GetParticleComponent(1)->SetOrderInLayer(35);
	Emanager->GetParticleComponent(1)->SetLoop(false);
	Emanager->GetParticleComponent(1)->SetMinSpeed(0.3f);
	Emanager->GetParticleComponent(1)->SetMaxSpeed(0.7f);
	Emanager->GetParticleComponent(1)->SetDuration(0.8f);
	Emanager->GetParticleComponent(1)->SetFadeOutTime(0.7f);
	Emanager->GetParticleComponent(1)->SetAmount(25);
	Emanager->GetParticleComponent(1)->SetAnimPlayer(L"../../Resource/Particles/defend/ParticleGuard.png",
		L"../../Resource/Json/SparkSheet/ParticleGuard_sprites.json",
		L"../../Resource/Json/SparkSheet/ParticleGuard_Guard_anim.json");
	Emanager->GetParticleComponent(1)->SetShowType(ParticleShowType::RandomSingle);
	Emanager->GetParticleComponent(1)->SetGravity(false);
	Emanager->GetParticleComponent(1)->SetSeeDirection(true);
	Emanager->GetParticleComponent(1)->SetDecreasing(true);
	Emanager->SetUnityValue(false);

	for (size_t i = 0; i < 9 ; i++)
	{
		GameObject* obj = new GameObject();
		obj->AddComponent<AnimationRenderer>();
		obj->SetName(std::string("Effect") + std::to_string(i));
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
		obj->GetTransform().SetPosition(9999.0f, 9999.0f);
		obj->GetComponent<AnimationRenderer>()->CreateBitmapResource(L"../../Resource/Particles/attack_circle_spreadsheet.png");
		obj->GetComponent<AnimationRenderer>()->SetSpriteSheet(L"../../Resource/Json/attack_circle_sprites.json");
		obj->GetComponent<AnimationRenderer>()->SetAnimationClip(L"../../Resource/Json/attack_circle_anim.json");
		obj->GetComponent<AnimationRenderer>()->GetAnimationPlayer()->Pause();
		AnimeList.push_back(obj);
	}
}

void EffectInstance::OnDestroy()
{
	Emanager = nullptr;
}

void EffectInstance::CallEffect(EffectType type, Vector2 info)
{
	effecttype = type;
	Emanager->SetEffectPosition(info.x, info.y);
	counttime = 0;
	
	switch (type)
	{
	case EffectType::ParryEffect:
		Emanager->GetParticleComponent(0)->Reset();
		Emanager->GetParticleComponent(0)->Play();
		break;

	case EffectType::GuardEffect:
		Emanager->GetParticleComponent(1)->Reset();
		Emanager->GetParticleComponent(1)->Play();
		break;
	}
	
}

void EffectInstance::ParryEffect()
{
	if (counttime < maxtime){
	Emanager->SetEffectValue(0, GetValue(0), GetValue(0), 1 - GetValue(3), true);
	Emanager->SetEffectValue(1, GetValue(1), GetValue(1), 1 - GetValue(2), true);
	Emanager->SetEffectValue(2, 343, 22, 1 - GetValue(3), true);
	}
	else
	{
		EndEffects();
	}
}

void EffectInstance::GuardEffect()
{
	if (counttime < maxtime){
	Emanager->SetEffectValue(3, GetValue(1), GetValue(1), 1 - GetValue(2), true);
	Emanager->SetEffectValue(4, 343, 22, 1 - GetValue(3), true);
	}
	else
	{
		EndEffects();
	}
}

void EffectInstance::ChargeEffect()
{
	if( counttime < maxtime2){
	Emanager->SetEffectValue(5, 378 - GetValue(4), 378 - GetValue(4), 1/* - GetValue(5)*/, true);
	Emanager->SetEffectValue(6, GetValue(4), GetValue(4), 1/* - GetValue(5)*/, true);
	chargeValue = GetValue(4);
	}
	else
	{
		EndEffects();
		/*HoldEffect();*/
	}
}

void EffectInstance::HoldEffect()
{
	CountMathTime += Singleton<GameTime>::GetInstance().GetDeltaTime();
	capacapacityWave >= 3.5f ? capacapacityWave = 5.0f : capacapacityWave += Singleton<GameTime>::GetInstance().GetDeltaTime() * 0.5f;
	Emanager->SetEffectValue(5, 378 - chargeValue, 378 - chargeValue, 1, true);
	Emanager->SetEffectValue(6, chargeValue - (GetValue(6) * 10), chargeValue - (GetValue(6)* 20), 1 - GetValue(5), true);
}

void EffectInstance::EndEffects()
{
	Emanager->SetOffEffect();
	effecttype = EffectType::None;
}

//증가 계산식
float EffectInstance::GetValue(size_t type)
{
	switch (type)
	{
	case 0:
	{
		float circle_outer = EasingList[EasingEffect::OutExpo](counttime);
		return circle_outer * 189;
	}
	case 1:
	{
		float circle_inner = EasingList[EasingEffect::OutExpo](counttime);
		return circle_inner * 302;
	}
	case 2:
	{
		float Capacity = EasingList[EasingEffect::InExpo](counttime);
		return Capacity;
	}
	case 3:
	{
		float line_horizon = EasingList[EasingEffect::OutExpo](counttime);
		return line_horizon;
	}
	case 4:
	{
		float circle_inner = EasingList[EasingEffect::OutExpo](counttime/6);
		return circle_inner * 189;
	}
	case 5:
	{
		//일렁임
		float Capacity = (std::sin(CountMathTime * /*(CountMathTime >= 3.0f ? 4.0f : 0.5f)*/capacapacityWave * PI) + 1.0f) * 0.5 * 0.3f;
		return Capacity;
	}
	case 6:
	{
		float circle_inner = std::sin(CountMathTime * PI);
		return circle_inner;
	}
	default:
		return 0.0f;
	}
}

