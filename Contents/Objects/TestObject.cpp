#include "TestObject.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"

void TestObject::OnStart()
{
	owner->SetRenderLayer(EngineData::RenderLayer::GameObject);
	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(L"../WorkSpace/HSK/Test/testA.png");
	//bitmapRenderer->SetOrderInLayer(-1); // 이거 그럼 나중에 밖으로 빼야할 수 있음 잘 적용되는지 몰루임
 	//size = bitmapRenderer->GetResource()->GetBitmap()->GetSize();
	//owner->GetTransform().SetUnityCoords(false);

	anim = owner->AddComponent<AnimationRenderer>();
	anim->CreateBitmapResource(L"../Resource/Particles/Test/FireEffectSheet.png");
	anim->SetSpriteSheet(L"../Resource/Json/Test_Paticles/FireEffectSheet_sprites.json");
	anim->SetAnimationClip(L"../Resource/Json/Test_Paticles/Fire_Idle_anim.json");
}

void TestObject::OnUpdate()
{

}

void TestObject::OnDestroy()
{
}


