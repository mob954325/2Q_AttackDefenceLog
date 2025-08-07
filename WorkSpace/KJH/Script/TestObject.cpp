#include "TestObject.h"
#include "Components/Base/GameObject.h"
#include <iostream>
#include "Systems/AudioSystem.h"
#include "Components/Camera/CameraManager.h"
#include "Scene/SceneManager.h"


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
		/*TestParticle->SetLoop(false);*/
		Emanager->SetOffEffect();
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
	mydeltatime = Singleton<GameTime>::GetInstance().GetDeltaTime();
	Emanager->CreateEffectObject(3);
	Emanager->CreateParticleObject();
	Emanager->SetEffectImage(0, L"../../Resource/Particles/circle_outer.png");
	Emanager->SetEffectImage(1, L"../../Resource/Particles/circle_inner.png");
	Emanager->SetEffectImage(2, L"../../Resource/Particles/line_horizon.png");
	TestParticle = Emanager->GetParticleComponent();
	TestParticle->SetBitmap(L"../../Resource/Particles/Test/Arrow.png");
	TestParticle->SetLoop(false);
	TestParticle->SetMinSpeed(0.3f);
	TestParticle->SetMaxSpeed(5.0f);
	TestParticle->SetDuration(0.5f);
	TestParticle->SetFadeOutTime(0.7f);
	TestParticle->SetAmount(50);
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

		return 0;
		break;

	case 1:

		return 0;
		break;

	case 2:

		return 0;
		break;
	}
}
