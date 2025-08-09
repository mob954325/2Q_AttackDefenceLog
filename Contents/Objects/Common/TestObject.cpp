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
	//bitmapRenderer->SetOrderInLayer(-1); // 이거 그럼 나중에 밖으로 빼야할 수 있음 잘 적용되는지 몰루임
 	//size = bitmapRenderer->GetResource()->GetBitmap()->GetSize();
	//owner->GetTransform().SetUnityCoords(false);

	// anim->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/Resource/Particles/Test/FireEffectSheet.png");
	// anim->SetSpriteSheet(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/Resource/Json/Test_Paticles/FireEffectSheet_sprites.json");
	// anim->SetAnimationClip(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/Resource/Json/Test_Paticles/Fire_Idle_anim.json");
}

void TestObject::OnUpdate()
{

}

void TestObject::OnDestroy()
{
}


