#include "TestObject.h"
#include "Components/Base/GameObject.h"
#include <iostream>
#include "Systems/AudioSystem.h"
#include "Components/Camera/CameraManager.h"

void TestObject::OnUpdate()
{
}

void TestObject::OnCreate()
{
	TestImage = owner->AddComponent<BitmapRenderer>();
	TestImage->CreateBitmapResource(L"../../Resource/UI/TestImage/test.png");
	owner->GetTransform().SetOffset(-TestImage->GetResource()->GetBitmap()->GetSize().width / 2, TestImage->GetResource()->GetBitmap()->GetSize().height / 2);
}

void TestObject::OnStart()
{
	/*owner->GetComponent<Transform>()->SetPosition(50.0f, 50.0f);*/
}

void TestObject::OnDestroy()
{
}
