#pragma once
#include "pch.h"
#include "Components/Rendering/RenderComponent.h"

/* 25.08.10 | 작성자 : 이성호
* 기능 : 비네트 효과를 이미지에 적용 시키는 컴포넌트
주의 : 해당 효과 랜더가 이미지의 랜더보다 나중에 출력됨

*/
// <example>
// #include "TestVignetteObject.h"
// #include "Components/Base/GameObject.h"
// #include "Application/AppPaths.h"
// 
// void TestVignetteObject::OnCreate()
// {
// 	vignette = owner->AddComponent<VignetteEffect>();
// 	bitmap = owner->AddComponent<BitmapRenderer>();
// }
// 
// void TestVignetteObject::OnStart()
// {
// 	bitmap->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Mouse\\testB.png");
// 	vignette->SetBitmap(bitmap->GetResource()->GetBitmap().Get());
// 	vignette->SetColor({ 1.0f, 0.0f,0.0f,1.0f });
// 	vignette->SetEffectSize(0.8f);
// 	vignette->SetStrength(0.4f);
// 
// 	vignette->SetOrderInLayer(10000);
// }
// </example>

/// <summary>
/// Vignette 효과를 bitmap 이미지에 적용 시키는 컴포넌트
/// </summary>
class VignetteEffect : public RenderComponent
{
public:
	void OnCreate() override;
	void OnStart() override;
	void Render(D2DRenderManager* manager);

	/// <summary>
	/// 효과를 적용 시킬 비트맵을 설정하는 함수
	/// </summary>
	void SetBitmap(ID2D1Bitmap1* pBitmap);

	/// <summary>
	/// 효과 크기를 설정하는 함수 ( 값이 클수록 효과의 범위가 커짐 )
	/// </summary>
	void SetEffectSize(float value);

	/// <summary>
	/// 효과의 강도를 설정하는 함수 ( 값이 클수록 효과가 더 선명하게 보임 )
	/// </summary>
	void SetStrength(float value);

	/// <summary>
	/// 효과의 색을 설정하는 함수 ( RGBA )
	/// </summary>
	/// <param name="color4F">D2D1_VECTOR_4F에 0.0f ~ 1.0f 값</param>
	void SetColor(D2D1_VECTOR_4F color4F);
private:
	Microsoft::WRL::ComPtr<ID2D1Effect> vignetteEffect;
	float effectSize = 1.0f;
	float strength = 1.0f;
	D2D1_VECTOR_4F color{};

	ID2D1Bitmap1* refBitmap;
};

