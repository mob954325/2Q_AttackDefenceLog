#include "TestVignetteObject.h"
#include "Components/Base/GameObject.h"
#include "Application/AppPaths.h"

void TestVignetteObject::OnCreate()
{
	vignette = owner->AddComponent<VignetteEffect>();
	bitmap = owner->AddComponent<BitmapRenderer>();
}

void TestVignetteObject::OnStart()
{
	bitmap->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Mouse\\testB.png");
	vignette->SetBitmap(bitmap->GetResource()->GetBitmap().Get());
	vignette->SetColor({ 1.0f, 0.0f,0.0f,1.0f });
	vignette->SetEffectSize(0.8f);
	vignette->SetStrength(0.4f);

	vignette->SetOrderInLayer(10000);
}