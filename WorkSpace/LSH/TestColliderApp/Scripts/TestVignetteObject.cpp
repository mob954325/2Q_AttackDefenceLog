#include "TestVignetteObject.h"
#include "Components/Base/GameObject.h"
#include "Application/AppPaths.h"
#include "math.h"
#include "Utils/GameTime.h"

#include "Datas/EngineData.h"

void TestVignetteObject::OnCreate()
{
	owner->GetTransform().SetUnityCoords(false);

	vignette = owner->AddComponent<VignetteEffect>();
	bitmap = owner->AddComponent<BitmapRenderer>();

	owner->GetTransform().SetOffset(EngineData::SceenWidth / 2, -EngineData::SceenHeight / 2);
	input = owner->AddComponent<InputSystem>();
}

void TestVignetteObject::OnStart()
{
	bitmap->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Mouse\\testB.png");
	bitmap->SetActive(false);
	float offsetX = 30.0f;
	float offsetY = 30.0f;


	D2D1_SIZE_F size = bitmap->GetResource()->GetBitmap()->GetSize();
	bitmap->SetFlipX(!bitmap->IsFlipX());
	owner->GetTransform().Translate({ size.width / 2, -size.height / 2 });

	vignette->SetBitmap(bitmap->GetResource()->GetBitmap().Get());
	vignette->SetColor({ 1.0f, 0.0f,0.0f,1.0f });
	vignette->SetEffectSize(0.8f);
	vignette->SetStrength(0.4f);

	vignette->SetOrderInLayer(10000);
}

void TestVignetteObject::OnUpdate()
{
	value += Singleton<GameTime>::GetInstance().GetDeltaTime() * 4.0f;

	float y = (std::sin(value) * 0.5f) + 0.5f;
	vignette->SetEffectSize(y);


	if (input->IsKeyDown('J'))
	{
		owner->GetTransform().Translate({ -1,0 });
	}
	if (input->IsKeyDown('L'))
	{
		owner->GetTransform().Translate({ 1,0 });
	}
	if (input->IsKeyDown('I'))
	{
		owner->GetTransform().Translate({ 0,1 });
	}
	if (input->IsKeyDown('K'))
	{
		owner->GetTransform().Translate({ 0,-1 });
	}

	if (input->IsKeyDown('1'))
	{
		bitmap->SetFlipX(!bitmap->IsFlipX());
	}
	if (input->IsKeyDown('2'))
	{
		bitmap->SetFlipY(!bitmap->IsFlipY());
	}
}