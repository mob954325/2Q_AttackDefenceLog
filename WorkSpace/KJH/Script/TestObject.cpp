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
		TestEffect->Setcircleoutervalue(50 + counttime, 1- counttime);
		TestEffect->Setcircleinnervalue(50 + counttime , 1- counttime);
		TestEffect->Setlinehorizonvalue(0, 0);
	}
	else if (eventvalue && counttime >= maxtime)
	{
		TestEffect->Setcircleoutervalue(0.0f, 0.0f);
		TestEffect->Setcircleinnervalue(0.0f , 0.0f);
		TestEffect->Setlinehorizonvalue(0.0f, 0.0f);
		eventvalue = false;
	}
}

void TestObject::OnCreate()
{
	/*TestImage = owner->AddComponent<BitmapRenderer>();
	TestImage->CreateBitmapResource(L"../../Resource/UI/TestImage/test.png");
	owner->GetTransform().SetOffset(-TestImage->GetResource()->GetBitmap()->GetSize().width / 2, TestImage->GetResource()->GetBitmap()->GetSize().height / 2);*/
	counttime = 0;
	TestEffect = owner->AddComponent<EffectComponent>();
	input = owner->AddComponent<InputSystem>();
}

void TestObject::OnStart()
{
	/*owner->GetComponent<Transform>()->SetPosition(50.0f, 50.0f);*/
	mydeltatime = Singleton<GameTime>::GetInstance().GetDeltaTime();
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
