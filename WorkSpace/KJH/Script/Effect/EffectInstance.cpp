#include "EffectInstance.h"
#include "Components/Base/GameObject.h"
#include <iostream>
#include "Systems/AudioSystem.h"
#include "Components/Camera/CameraManager.h"
#include "Scene/SceneManager.h"
#include "Math/EasingFunction.h"


//Update로 프레임마다 이펙트들 업데이트
void EffectInstance::OnUpdate()
{
	if (eventvalue && counttime < maxtime)
	{
		counttime += Singleton<GameTime>::GetInstance().GetDeltaTime();
		Emanager->SetEffectValue(0, GetValue(0), GetValue(0), 1 - GetValue(3), true);
		Emanager->SetEffectValue(1, GetValue(1), GetValue(1), 1 - GetValue(2), true);
		Emanager->SetEffectValue(2, 343, 22, 1 - GetValue(3), true);
		std::cout << counttime << std::endl;

	}
	else if (eventvalue && counttime >= maxtime)
	{
		Emanager->SetOffEffect();
		eventvalue = false;
	}

	if (eventvalue2 && counttime < maxtime)
	{

		counttime += Singleton<GameTime>::GetInstance().GetDeltaTime();
		Emanager->SetEffectValue(3, GetValue(1), GetValue(1), 1 - GetValue(2), true);
		Emanager->SetEffectValue(4, 343, 22, 1 - GetValue(3), true);
		std::cout << counttime << std::endl;

	}
	else if (eventvalue2 && counttime >= maxtime)
	{
		Emanager->SetOffEffect();
		eventvalue2 = false;
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
	Emanager->CreateEffectObject(5);
	Emanager->CreateParticleObject(2);
	//패리
	Emanager->SetEffectImage(0, L"../../Resource/Particles/circle_outer.png");
	Emanager->SetEffectImage(1, L"../../Resource/Particles/circle_inner.png");
	Emanager->SetEffectImage(2, L"../../Resource/Particles/line_horizon.png");
	//방어
	Emanager->SetEffectImage(3, L"../../Resource/Particles/defend/circle_inner.png");
	Emanager->SetEffectImage(4, L"../../Resource/Particles/defend/horizon_line.png");



	Emanager->SetLayer(0, 30);
	Emanager->SetLayer(1, 31);
	Emanager->SetLayer(2, 32);
	Emanager->SetLayer(3, 33);
	Emanager->SetLayer(4, 34);



	Emanager->GetParticleComponent(0)->SetOrderInLayer(35);
	Emanager->GetParticleComponent(0)->SetLoop(false);
	Emanager->GetParticleComponent(0)->SetMinSpeed(0.3f);
	Emanager->GetParticleComponent(0)->SetMaxSpeed(0.7f);
	Emanager->GetParticleComponent(0)->SetDuration(0.8f);
	Emanager->GetParticleComponent(0)->SetFadeOutTime(0.7f);
	Emanager->GetParticleComponent(0)->SetAmount(25);
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
}

void EffectInstance::OnDestroy()
{

}

//좌표 넣고 원하는곳에서 재생되도록 설정 예정
void EffectInstance::CallGuardEffect()
{
	Emanager->GetParticleComponent(1)->Reset();
	eventvalue2 = true;
	counttime = 0;
	Emanager->GetParticleComponent(1)->Play();
}

//좌표 넣고 원하는곳에서 재생되도록 설정 예정
void EffectInstance::CallParryEffect()
{
	Emanager->GetParticleComponent(0)->Reset();
	eventvalue = true;
	counttime = 0;
	Emanager->GetParticleComponent(0)->Play();
}

//좌표 넣고 원하는곳에서 재생되도록 설정 예정
void EffectInstance::CallNomalEffect()
{

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
		break;
	}
	case 1:
	{
		float circle_inner = EasingList[EasingEffect::OutExpo](counttime);
		return circle_inner * 302;
		break;
	}

	case 2:
	{
		float Capacity = EasingList[EasingEffect::InExpo](counttime);
		return Capacity;
		break;
	}
	case 3:
	{
		float line_horizon = EasingList[EasingEffect::OutExpo](counttime);
		/*return sin(line_horizon * PI)* 343.0f;*/
		/*return line_horizon * 343.0f;*/
		return line_horizon;
		break;
	}
	}
}

