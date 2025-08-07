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
		Emanager->GetParticleComponent()->Render();

	}
	else if (eventvalue && counttime >= maxtime)
	{

		eventvalue = false;
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
	/*owner->GetComponent<Transform>()->SetPosition(50.0f, 50.0f);*/
	mydeltatime = Singleton<GameTime>::GetInstance().GetDeltaTime();
	Emanager->CreateEffectObject(3);
	Emanager->CreateParticleObject();
	Emanager->SetEffectImage(0, L"../../Resource/Particles/circle_outer.png");
	Emanager->SetEffectImage(1, L"../../Resource/Particles/circle_inner.png");
	Emanager->SetEffectImage(2, L"../../Resource/Particles/line_horizon.png");
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
	}
}
