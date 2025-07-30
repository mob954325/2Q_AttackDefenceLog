#include "Slider.h"
#include "Components/Base/GameObject.h"
#include "Platform/Input.h"
#include "Datas/EngineData.h"

void Slider::OnStart()
{
	GaugeBackground = owner->AddComponent<BitmapRenderer>();
	GaugeBackground->CreateBitmapResource(L"../../Resource/UI/TestGauge/backgroundBar.png");
	GaugeBar = owner->AddComponent<BitmapRenderer>();
	GaugeBar->CreateBitmapResource(L"../../Resource/UI/TestGauge/Bar.png");
}

void Slider::Update()
{

}


//void Slider::SetGaugeBarRect(float width)
//{
//	Vector2 position = owner->GetTransform().GetPosition();
//	if (pivotIsLeft)
//	{
//		GaugeBarRect.right += width;
//	}
//	else
//	{
//		GaugeBarRect.right -= width; // 우측 상단을 기준으로 충돌 범위 설정
//	}
//}

void Slider::SetPivotSide(bool isLeft)
{
	pivotIsLeft = isLeft;
}

void Slider::SetGaugeBackgroundImage(std::wstring path)
{
	GaugeBackground->CreateBitmapResource(path);
}

BitmapRenderer* Slider::GetGaugeBackgroundImage()
{
	return GaugeBackground;
}

void Slider::SetGaugeBarImage(std::wstring path)
{
	GaugeBar->CreateBitmapResource(path);
}

BitmapRenderer* Slider::GetGaugeBarImage()
{
	return GaugeBar;
}
