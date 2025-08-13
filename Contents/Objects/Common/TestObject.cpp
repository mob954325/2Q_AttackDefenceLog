#include "TestObject.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"

void TestObject::OnCreate()
{
	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	anim = owner->AddComponent<AnimationRenderer>();
}

void TestObject::OnStart()
{
	owner->SetRenderLayer(EngineData::RenderLayer::GameObject);
	bitmapRenderer->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Mouse\\testA.png");
}

void TestObject::OnUpdate()
{

}

void TestObject::OnDestroy()
{
}


