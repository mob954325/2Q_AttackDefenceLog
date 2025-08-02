#include "TestObject2.h"
#include "Components/Base/GameObject.h"
#include <iostream>
#include "Systems/AudioSystem.h"
#include "Components/Camera/CameraManager.h"
#include "Components/UI/Slider.h"

void TestObject2::OnUpdate()
{

}

void TestObject2::OnCreate()
{
	owner->GetTransform().SetPosition(-500, 50);
	TestImage = owner->AddComponent<BitmapRenderer>();
	TestImage->CreateBitmapResource(L"../../Resource/UI/TestImage/test2.png");
	owner->GetTransform().SetOffset(-TestImage->GetResource()->GetBitmap()->GetSize().width / 2, TestImage->GetResource()->GetBitmap()->GetSize().height / 2);
	owner->AddComponent<Slider>();
}

void TestObject2::OnStart()
{

}

void TestObject2::OnDestroy()
{

}
