#include "EffectInstance.h"
#include "Components/Base/GameObject.h"
#include <iostream>
#include "Systems/AudioSystem.h"
#include "Components/Camera/CameraManager.h"
#include "Scene/SceneManager.h"
#include "Math/EasingFunction.h"
#include <cmath>
#include "Application/AppPaths.h"


//Update로 프레임마다 이펙트들 업데이트
void EffectInstance::OnUpdate()
{
	/*if (CheckPlayAnime && AnimeCount < Animeduration)
	{
		AnimeCount += Singleton<GameTime>::GetInstance().GetDeltaTime();
	}
	else if (CheckPlayAnime && AnimeCount >= Animeduration)
	{
		CheckPlayAnime = false;
		AnimeList[AnimeNum]->GetComponent<AnimationRenderer>()->SetActive(false);
		AnimeList[AnimeNum]->GetComponent<AnimationRenderer>()->GetAnimationPlayer()->Pause();
		AnimeList[AnimeNum]->GetComponent<AnimationRenderer>()->GetAnimationPlayer()->Reset();
	}*/


	float dt = Singleton<GameTime>::GetInstance().GetDeltaTime();
	for (size_t i = 0; i < AnimeList.size(); ++i) {
		auto& state = AnimeStates[i];
		if (!state.playing) continue;

		state.t += dt;
		if (state.t >= state.duration) {
			state.playing = false;
			state.t = 0.0f;

			auto* r = AnimeList[i]->GetComponent<AnimationRenderer>();
			r->SetActive(false);
			auto* p = r->GetAnimationPlayer();
			p->Pause();
			p->Reset();
		}
	}

	if (effecttype == EffectType::None) return;
	else
	{
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
}

//변수 초기화 및 Emanager 등록
void EffectInstance::OnCreate()
{
	counttime = 0;
	Emanager = owner->AddComponent<EffectManager>();

	for (size_t i = 0; i < 9; i++)
	{
		GameObject* obj = new GameObject();
		obj->GetTransform().SetUnityCoords(false);
		obj->SetRenderLayer(EngineData::RenderLayer::UI);
		auto ar = obj->AddComponent<AnimationRenderer>();
		ar->SetOrderInLayer(131);
		obj->SetName(std::string("Effect") + std::to_string(i));
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
		obj->GetComponent<AnimationRenderer>()->SetActive(false);
		obj->GetComponent<AnimationRenderer>()->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Particles\\attack_circle_spreadsheet.png");
		obj->GetComponent<AnimationRenderer>()->SetSpriteSheet(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Json\\attack_circle_sprites.json");
		obj->GetComponent<AnimationRenderer>()->SetAnimationClip(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Json\\attack_circle_anim.json");
		obj->GetComponent<AnimationRenderer>()->GetAnimationPlayer()->Pause();
		AnimeList.push_back(obj);
	}

	Emanager->CreateEffectObject(7);
	Emanager->CreateParticleObject(2);

	//패리
	Emanager->SetEffectImage(0, Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Particles\\circle_outer.png");
	Emanager->SetEffectImage(1, Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Particles\\circle_inner.png");
	Emanager->SetEffectImage(2, Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Particles\\line_horizon.png");
	//방어
	Emanager->SetEffectImage(3, Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Particles\\defend\\circle_inner.png");
	Emanager->SetEffectImage(4, Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Particles\\defend\\horizon_line.png");
	Emanager->SetEffectImage(5, Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Particles\\nomal\\combo_node_outer_circle.png");
	Emanager->SetEffectImage(6, Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Particles\\nomal\\combo_node_inner_circle.png");



	Emanager->SetLayer(0, 230);
	Emanager->SetLayer(1, 231);
	Emanager->SetLayer(2, 232);
	Emanager->SetLayer(3, 233);
	Emanager->SetLayer(4, 234);
	Emanager->SetLayer(5, 235);
	Emanager->SetLayer(6, 235);

	Emanager->GetParticleComponent(0)->SetOrderInLayer(235);
	Emanager->GetParticleComponent(0)->SetLoop(false);
	Emanager->GetParticleComponent(0)->SetMinSpeed(1.3f);
	Emanager->GetParticleComponent(0)->SetMaxSpeed(3.0f); 
	Emanager->GetParticleComponent(0)->SetDuration(0.8f);
	Emanager->GetParticleComponent(0)->SetFadeOutTime(0.7f);
	Emanager->GetParticleComponent(0)->SetAmount(20);
	Emanager->GetParticleComponent(0)->SetAnimPlayer(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Particles\\SparkSheet.png",
		Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Json\\SparkSheet\\SparkSheet_sprites.json",
		Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Json\\SparkSheet\\Red_Spark_anim.json");
	Emanager->GetParticleComponent(0)->SetShowType(ParticleShowType::RandomSingle);
	Emanager->GetParticleComponent(0)->SetGravity(false);
	Emanager->GetParticleComponent(0)->SetSeeDirection(true);
	Emanager->GetParticleComponent(0)->SetDecreasing(true);

	Emanager->GetParticleComponent(1)->SetOrderInLayer(235);
	Emanager->GetParticleComponent(1)->SetLoop(false);
	Emanager->GetParticleComponent(1)->SetMinSpeed(0.3f);
	Emanager->GetParticleComponent(1)->SetMaxSpeed(0.7f);
	Emanager->GetParticleComponent(1)->SetDuration(0.8f);
	Emanager->GetParticleComponent(1)->SetFadeOutTime(0.7f);
	Emanager->GetParticleComponent(1)->SetAmount(25);
	Emanager->GetParticleComponent(1)->SetAnimPlayer(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Particles\\defend\\ParticleGuard.png",
		Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Json\\SparkSheet\\ParticleGuard_sprites.json",
		Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Json\\SparkSheet\\ParticleGuard_Guard_anim.json");
	Emanager->GetParticleComponent(1)->SetShowType(ParticleShowType::RandomSingle);
	Emanager->GetParticleComponent(1)->SetGravity(false);
	Emanager->GetParticleComponent(1)->SetSeeDirection(true);
	Emanager->GetParticleComponent(1)->SetDecreasing(true);
	Emanager->SetUnityValue(false);
}

//초기 이미시 셋팅 및  파티클 수치 설정
void EffectInstance::OnStart()
{
	//슬롯초기화
	AnimeStates.resize(AnimeList.size());
}

void EffectInstance::OnDestroy()
{
	Emanager = nullptr;
}

// 8.09 추가, 외부에서 쓰기 쉽게 랩핑함
void EffectInstance::DoParry(int n) 
{
	CallEffect(EffectType::ParryEffect, nodePos[n]); 
}
void EffectInstance::DoGuard(int n) { CallEffect(EffectType::GuardEffect, nodePos[n]); }


void EffectInstance::CallEffect(EffectType type, const Vector2& info)
{
	effecttype = type;
	Emanager->SetEffectPosition(info.x, info.y);
	counttime = 0;

	std::cout << "u info : " << info << std::endl;
	std::cout << "position : " << owner->GetTransform().GetPosition() << std::endl;

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
	if (counttime < maxtime) {
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
	if (counttime < maxtime) {
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
	if (counttime < maxtime2) {
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
	Emanager->SetEffectValue(6, chargeValue - (GetValue(6) * 10), chargeValue - (GetValue(6) * 20), 1 - GetValue(5), true);
}

void EffectInstance::EndEffects()
{
	Emanager->SetOffEffect();
	effecttype = EffectType::None;
}

void EffectInstance::SetAnimePosition(const std::vector<Vector2>& vectorList)
{
	if (vectorList.size() != 9) return;
	for (size_t i = 0; i < 9; ++i)
	{
		AnimeList[i]->GetTransform().SetPosition(vectorList[i].x, vectorList[i].y);
		// nodePos.push_back(vectorList[i]);
	}

	nodePos = vectorList;
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
		float circle_inner = EasingList[EasingEffect::OutExpo](counttime / 6);
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

void EffectInstance::CallAnime(size_t num)
{
	/*CheckPlayAnime = true;
	AnimeNum = num;
	AnimeList[AnimeNum]->GetComponent<AnimationRenderer>()->GetAnimationPlayer()->Play();
	AnimeCount = 0;*/
	if (num >= AnimeList.size()) return;

	auto* r = AnimeList[num]->GetComponent<AnimationRenderer>();
	r->SetActive(true);
	auto* p = r->GetAnimationPlayer();
	p->Play();

	auto& s = AnimeStates[num];
	s.playing = true;
	s.t = 0.0f;
	s.duration = Animeduration; // 슬롯마다 다르게 가능
}

void EffectInstance::StopAnime(size_t num)
{
	if (num >= AnimeList.size()) return;
	auto& s = AnimeStates[num];
	if (!s.playing) return;

	s.playing = false;
	s.t = 0.0f;

	auto* r = AnimeList[num]->GetComponent<AnimationRenderer>();
	r->SetActive(false);
	auto* p = r->GetAnimationPlayer();
	p->Pause();
	p->Reset();
}

void EffectInstance::StopAllAnime()
{
	for (size_t i = 0; i < AnimeList.size(); ++i) StopAnime(i);
}
