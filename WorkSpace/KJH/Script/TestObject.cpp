#include "TestObject.h"
#include "Components/Base/GameObject.h"
#include <iostream>
#include "Systems/AudioSystem.h"
#include "Components/Camera/CameraManager.h"


void TestObject::OnUpdate()
{
	CheckInput();

	if (eventvalue && counttime < maxtime)
	{
		counttime += mydeltatime;
		Emanager->SetEffectValue(0, 189, 189, 1, true);
		Emanager->SetEffectValue(1, 302, 307, 1, true);
		Emanager->SetEffectValue(2, 343, 22, 1, true);
	}
	else if (eventvalue && counttime >= maxtime)
	{
		TestParticle->SetLoop(false);
		Emanager->SetOffEffect();
	}
}

void TestObject::OnCreate()
{
	/*TestImage = owner->AddComponent<BitmapRenderer>();
	TestImage->CreateBitmapResource(L"../../Resource/UI/TestImage/test.png");
	owner->GetTransform().SetOffset(-TestImage->GetResource()->GetBitmap()->GetSize().width / 2, TestImage->GetResource()->GetBitmap()->GetSize().height / 2);*/
	counttime = 0;
	input = owner->AddComponent<InputSystem>();
	Emanager = owner->AddComponent<EffectManager>();
}

void TestObject::OnStart()
{
	mydeltatime = Singleton<GameTime>::GetInstance().GetDeltaTime();
	Emanager->CreateEffectObject(3);
	Emanager->CreateParticleObject();
	Emanager->SetEffectImage(0, L"../../Resource/Particles/circle_outer.png");
	Emanager->SetEffectImage(1, L"../../Resource/Particles/circle_inner.png");
	Emanager->SetEffectImage(2, L"../../Resource/Particles/line_horizon.png");
	//TestParticle = Emanager->GetParticleComponent();
	//TestParticle->SetBitmap(L"../../Resource/Particles/Test/Arrow.png");
	//TestParticle->SetLoop(true);
	//TestParticle->SetMinSpeed(0.3f);
	//TestParticle->SetMaxSpeed(5.0f);
	//TestParticle->SetDuration(0.8f);
	//TestParticle->SetFadeOutTime(0.7f);
	//TestParticle->SetAmount(50);
	//TestParticle->SetAnimPlayer(L"../../Resource/Particles/SparkSheet.png",
	//	L"../../Resource/Json/SparkSheet/SparkSheet_sprites.json",
	//	L"../../Resource/Json/SparkSheet/Red_Spark_anim.json");
	//TestParticle->SetShowType(ParticleShowType::RandomSingle);
	//TestParticle->SetGravity(true);
	//TestParticle->SetSeeDirection(true);
	//TestParticle->SetDecreasing(true);

}

void TestObject::OnDestroy()
{

}

void TestObject::CheckInput()
{
	if (input->IsKeyPressed('N'))
	{
		eventvalue = true;
		counttime = 0;
		/*TestParticle->Play();*/
	}
}
