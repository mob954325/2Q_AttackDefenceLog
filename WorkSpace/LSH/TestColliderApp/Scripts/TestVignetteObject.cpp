#include "TestVignetteObject.h"
#include "Components/Base/GameObject.h"
#include "Application/AppPaths.h"
#include "math.h"
#include "Utils/GameTime.h"

void TestVignetteObject::OnCreate()
{
	//vignette = owner->AddComponent<VignetteEffect>();
	bitmap = owner->AddComponent<BitmapRenderer>();
	input = owner->AddComponent<InputSystem>();
}

void TestVignetteObject::OnStart()
{
	bitmap->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Mouse\\testB.png");
	// vignette->SetBitmap(bitmap->GetResource()->GetBitmap().Get());
	// vignette->SetColor({ 1.0f, 0.0f,0.0f,1.0f });
	// vignette->SetEffectSize(0.8f);
	// vignette->SetStrength(0.4f);
	// 
	// vignette->SetOrderInLayer(10000);

	owner->GetTransform().SetUnityCoords(false);

	float offsetX = 30.0f;
	float offsetY = 30.0f;
	std::vector<Vector2> vec
	{
		{offsetX + 0,  offsetY + 50},
		{offsetX + 14, offsetY +  15},
		{offsetX + 47, offsetY +  15},
		{offsetX + 23, offsetY +  -7},
		{offsetX + 29, offsetY +  -40},
		{offsetX + 0,  offsetY + -20},
		{offsetX + -29, offsetY + -40},
		{offsetX + -23, offsetY + -7},
		{offsetX + -47, offsetY + 15},
		{offsetX + -14, offsetY + 15}
	};

	bitmap->SetClipingPosition(vec);
}

void TestVignetteObject::OnUpdate()
{
	value += Singleton<GameTime>::GetInstance().GetDeltaTime() * 4.0f;

	float y = (std::sin(value) * 0.5f) + 0.5f;
	//vignette->SetEffectSize(y);


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
}