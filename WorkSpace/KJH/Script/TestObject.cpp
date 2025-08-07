#include "TestObject.h"
#include "Components/Base/GameObject.h"
#include <iostream>
#include "Systems/AudioSystem.h"
#include "Components/Camera/CameraManager.h"
#include "Scene/SceneManager.h"
#include "Math/EasingFunction.h"


void TestObject::OnUpdate()
{
	CheckInput();

	if (eventvalue && counttime < maxtime)
	{
		
		counttime += Singleton<GameTime>::GetInstance().GetDeltaTime();
		Emanager->SetEffectValue(0, GetValue(0), GetValue(0), 1, true);
		Emanager->SetEffectValue(1, GetValue(1), GetValue(1), 1 - GetValue(2), true);
		Emanager->SetEffectValue(2, 343 , 22, 1 -  GetValue(3), true);
		std::cout << counttime << std::endl;
	
	}
	else if (eventvalue && counttime >= maxtime)
	{
		/*TestParticle->SetLoop(false);*/
		Emanager->SetOffEffect();
		eventvalue = false;
	}

	handleObject->GetTransform().SetPosition(owner->GetComponent<Slider>()->GetGaugeRectValue().right, owner->GetComponent<Slider>()->GetGaugeRectValue().bottom/2);
}

void TestObject::OnCreate()
{
	owner->AddComponent<Slider>();
	/*TestImage = owner->AddComponent<BitmapRenderer>();
	TestImage->CreateBitmapResource(L"../../Resource/UI/TestImage/test.png");
	owner->GetTransform().SetOffset(-TestImage->GetResource()->GetBitmap()->GetSize().width / 2, TestImage->GetResource()->GetBitmap()->GetSize().height / 2);*/
	counttime = 0;
	input = owner->AddComponent<InputSystem>();
	Emanager = owner->AddComponent<EffectManager>();
	/*AnimObject = owner->AddComponent<AnimationRenderer>();*/
	

	GameObject* Test = new GameObject();
	Test->AddComponent<AnimationRenderer>();
	Test->SetName("AnimeObject");
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(Test);
	handleObject = Test;

	AnimObject = handleObject->GetComponent<AnimationRenderer>();
	
	

}

void TestObject::OnStart()
{
	Emanager->CreateEffectObject(3);
	Emanager->CreateParticleObject();
	Emanager->SetEffectImage(0, L"../../Resource/Particles/circle_outer.png");
	Emanager->SetEffectImage(1, L"../../Resource/Particles/circle_inner.png");
	Emanager->SetEffectImage(2, L"../../Resource/Particles/line_horizon.png");
	Emanager->SetLayer(0, 30);
	Emanager->SetLayer(1, 31);
	Emanager->SetLayer(2, 32);


	TestParticle = Emanager->GetParticleComponent();
	TestParticle->SetBitmap(L"../../Resource/Particles/Test/Arrow.png");
	TestParticle->SetOrderInLayer(35);
	TestParticle->SetLoop(false);
	TestParticle->SetMinSpeed(0.3f);
	TestParticle->SetMaxSpeed(0.7f);
	TestParticle->SetDuration(0.8f);
	TestParticle->SetFadeOutTime(0.7f);
	TestParticle->SetAmount(25);
	TestParticle->SetAnimPlayer(L"../../Resource/Particles/SparkSheet.png",
		L"../../Resource/Json/SparkSheet/SparkSheet_sprites.json",
		L"../../Resource/Json/SparkSheet/Red_Spark_anim.json");
	TestParticle->SetShowType(ParticleShowType::RandomSingle);
	TestParticle->SetGravity(false);
	TestParticle->SetSeeDirection(true);
	TestParticle->SetDecreasing(true);

	AnimObject->CreateBitmapResource(L"../../Resource/Dance/Dance.png");
	AnimObject->SetSpriteSheet(L"../../Resource/Dance/Dance_sprites.json");
	AnimObject->SetAnimationClip(L"../../Resource/Dance/Dance_Dance_anim.json");

	AnimObject->GetAnimationPlayer().Play();
	AnimObject->SetOrderInLayer(15);

	/*owner->GetComponent<Slider>()->ButtonShow(false);*/


}

void TestObject::OnDestroy()
{
	/*AnimPlayer = nullptr;*/
}

void TestObject::CheckInput()
{
	if (input->IsKeyPressed('N'))
	{
		TestParticle->Reset();
		eventvalue = true;
		counttime = 0;
		TestParticle->Play();
	}



	if (input->IsKeyDown('J'))
	{
		owner->GetComponent<Slider>()->ChangeGauge(-1);
		owner->GetComponent<Slider>()->ChangeButtonPosition(-1);
		std::cout << "w 입력됨" << std::endl;
	}
	if (input->IsKeyDown('K'))
	{
		owner->GetComponent<Slider>()->ChangeGauge(1);
		owner->GetComponent<Slider>()->ChangeButtonPosition(1);
		std::cout << "s 입력됨" << std::endl;
	}

}



float TestObject::GetValue(size_t type)
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
