#include "Slider.h"
#include "Components/Base/GameObject.h"
#include "Platform/Input.h"
#include "Datas/EngineData.h"

void Slider::OnStart()
{
	GaugeBackground = owner->AddComponent<BitmapRenderer>();
	GaugeBackground->CreateBitmapResource(L"../../Resource/UI/TestGauge/backgroundBar.png");
	
	GaugeBar = owner->AddComponent<BitmapRenderer>();
	GaugeBar->SetUseCustomRect(true);
	GaugeBar->SetOrderInLayer(2);
	GaugeBar->CreateBitmapResource(L"../../Resource/UI/TestGauge/Bar.png");
	D2D1_SIZE_F size = GaugeBar->GetResource()->GetBitmap()->GetSize();
	GaugeBarRect.bottom = size.height;
	GaugeBarRect.right = size.width/2;

	BarButton = owner->AddComponent<BitmapRenderer>();
	BarButton->SetUseCustomRect(true);
	BarButton->SetOrderInLayer(3);
	BarButton->CreateBitmapResource(L"../../Resource/UI/TestGauge/BarBotton.png");
	D2D1_SIZE_F sizeButton = BarButton->GetResource()->GetBitmap()->GetSize();
	BarButSrctonRect.bottom = sizeButton.height;
	BarButSrctonRect.right = sizeButton.width;
	ButtonDestRect.bottom = sizeButton.height;
	ButtonDestRect.left = size.width / 2 - sizeButton.width/2;
	ButtonDestRect.right = size.width / 2 + sizeButton.width/2;
}

void Slider::Update()
{
	GaugeBar->SetSrcRect(GetGaugeRectValue());
	GaugeBar->SetDestRect(GetGaugeRectValue());

	BarButton->SetSrcRect(BarButSrctonRect);
	BarButton->SetDestRect(ButtonDestRect);
}


//void Slider::SetPivotSide(bool isLeft)
//{
//	pivotIsLeft = isLeft;
//}

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

void Slider::SetGaugeButtonImage(std::wstring path)
{
	BarButton->CreateBitmapResource(path);
}

BitmapRenderer* Slider::GetGaugeButtonImage()
{
	return BarButton;
}

void Slider::SetGaugeRectValue()
{
	GaugeBarRect = GaugeBar->GetDestRect();
}

D2D1_RECT_F Slider::GetGaugeRectValue()
{
	return GaugeBarRect;
}

void Slider::ChangeGauge(float x)
{
	D2D1_SIZE_F size = GaugeBar->GetResource()->GetBitmap()->GetSize();
	if (pivotIsLeft) {
		if ((GaugeBarRect.right < size.width && GaugeBarRect.right > 0))
		{
			GaugeBarRect.right += x;
		}
		else
		{
			if (GaugeBarRect.right >= size.width) { GaugeBarRect.right = size.width - 0.1f; }
			if (GaugeBarRect.right <= 0) { GaugeBarRect.right = 0.1f; }
		}
	}
	else {
		if ((GaugeBarRect.right < size.width && GaugeBarRect.right > 0))
		{
			GaugeBarRect.right -= x;
		}
		else
		{
			if (GaugeBarRect.right >= -size.width) { GaugeBarRect.right = -size.width + 0.1f; }
			if (GaugeBarRect.right >= 0) { GaugeBarRect.right = -0.1f; }
		}
	}
}

//x´Â ÁÂÇ¥°ª
void Slider::ChangeButtonPosition(float x)
{
	/*ButtonDestRect.left = size.width / 2 - sizeButton.width / 2;
	ButtonDestRect.right = size.width / 2 + sizeButton.width / 2;*/
	D2D1_SIZE_F size = GaugeBar->GetResource()->GetBitmap()->GetSize();
	D2D1_SIZE_F sizeButton = BarButton->GetResource()->GetBitmap()->GetSize();
	if (pivotIsLeft) {
		if ((ButtonDestRect.right -sizeButton.width / 2 < size.width && ButtonDestRect.right - sizeButton.width / 2 > 0))
		{
			ButtonDestRect.left += x;
			ButtonDestRect.right += x;
		}
		else
		{
			if (ButtonDestRect.right - sizeButton.width / 2 >= size.width) { 
				ButtonDestRect.left = size.width - sizeButton.width / 2 - 0.1f;
				ButtonDestRect.right = size.width + sizeButton.width /2 - 0.1f;				
			}
			if (ButtonDestRect.right - sizeButton.width / 2 <= 0) {
				ButtonDestRect.left = 0 - sizeButton.width / 2 + 0.1f;
				ButtonDestRect.right = 0 + sizeButton.width / 2 + 0.1f;
			}
		}
	}
	//else {
	//	if ((GaugeBarRect.right < size.width && GaugeBarRect.right > 0))
	//	{
	//		GaugeBarRect.right -= x;
	//	}
	//	else
	//	{
	//		if (GaugeBarRect.right >= -size.width) { GaugeBarRect.right = -size.width + 0.1f; }
	//		if (GaugeBarRect.right >= 0) { GaugeBarRect.right = -0.1f; }
	//	}
	//}
}

void Slider::ButtShow(bool setvalue)
{
	BarButton->SetActive(setvalue);
}

bool Slider::IsMouseOver(const Vector2& mousePos) const
{
	return false;
}

