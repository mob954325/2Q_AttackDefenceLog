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
	size = GaugeBar->GetResource()->GetBitmap()->GetSize();
	GaugeBarRect.bottom = size.height;
	GaugeBarRect.right = size.width/2;

	BarButton = owner->AddComponent<BitmapRenderer>();
	BarButton->SetUseCustomRect(true);
	BarButton->SetOrderInLayer(3);
	BarButton->CreateBitmapResource(L"../../Resource/UI/TestGauge/BarBotton.png");

	sizeButton = BarButton->GetResource()->GetBitmap()->GetSize();

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

	ButtonEvent();

	//std::cout << BarButSrctonRect.left << std::endl;
	//std::cout << BarButSrctonRect.right << std::endl;
	//std::cout << BarButSrctonRect.top << std::endl;
	//std::cout << BarButSrctonRect.bottom << std::endl;



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
	/*D2D1_SIZE_F size = GaugeBar->GetResource()->GetBitmap()->GetSize();*/
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

//x는 좌표값
void Slider::ChangeButtonPosition(float x)
{
	/*ButtonDestRect.left = size.width / 2 - sizeButton.width / 2;
	ButtonDestRect.right = size.width / 2 + sizeButton.width / 2;*/
	/*D2D1_SIZE_F size = GaugeBar->GetResource()->GetBitmap()->GetSize();
	D2D1_SIZE_F sizeButton = BarButton->GetResource()->GetBitmap()->GetSize();*/
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

size_t Slider::AddOnClickEvent(std::function<void()> fn)
{
	//이벤트를 등록하고 그 ID를 return
	size_t ID = onClickEvent.Add(fn);
	return ID;
}

void Slider::RemoveOnClickEventById(size_t id)
{
	onClickEvent.RemoveByID(id);
}

bool Slider::IsMouseOver(const Vector2& mousePos) const
{
	return mousePos.x >= ButtonRect.left && // 왼쪽
		mousePos.x <= ButtonRect.right &&	// 오른쪽 
		mousePos.y >= ButtonRect.top &&		// 위
		mousePos.y <= ButtonRect.bottom;	// 아래
}

bool Slider::IsMouseOverBackground(const Vector2& mousePos) const
{
	return mousePos.x >= BackGroundRect.left && // 왼쪽
		mousePos.x <= BackGroundRect.right &&	// 오른쪽 
		mousePos.y >= BackGroundRect.top &&		// 위
		mousePos.y <= BackGroundRect.bottom;	// 아래
}

void Slider::ButtonEvent()
{
	/*D2D1_SIZE_F size = GaugeBar->GetResource()->GetBitmap()->GetSize();*/
	Vector2 mouseVec = { Input::MouseX, Input::MouseY };
	
	ButtonRect = ButtonDestRect;
	BackGroundRect = { 0, 0 , size.width , size.height };

	if (owner->GetTransform().IsUnityCoords())
	{
		ButtonRect.left += EngineData::SceenWidth/2 + owner->GetTransform().GetPosition().x;
		ButtonRect.right += EngineData::SceenWidth / 2 + owner->GetTransform().GetPosition().x;
		ButtonRect.top += EngineData::SceenHeight/2 - owner->GetTransform().GetPosition().y;
		ButtonRect.bottom += EngineData::SceenHeight/2 - owner->GetTransform().GetPosition().y;

		BackGroundRect.left += EngineData::SceenWidth / 2 + owner->GetTransform().GetPosition().x;
		BackGroundRect.right += EngineData::SceenWidth / 2 + owner->GetTransform().GetPosition().x;
		BackGroundRect.top += EngineData::SceenHeight / 2 - owner->GetTransform().GetPosition().y;
		BackGroundRect.bottom += EngineData::SceenHeight / 2 - owner->GetTransform().GetPosition().y;
	}

	//std::cout << ButtonRect.left << std::endl;
	//std::cout << ButtonDestRect.left << std::endl;
	/*std::cout << BackGroundRect.right << std::endl;*/

	//std::cout << "asdf ::::: " << Input::MouseDeltaX << std::endl;

	//std::cout << Input::MouseDeltaX << std::endl;
	/*std::cout << BackGroundRect.right << std::endl;*/
	
	
	if (IsMouseOver(mouseVec))
	{
		OnButton = true;
		std::cout << "마우스 버튼 위 지나감 감지" << std::endl;

		if (Input::leftButtonDown)
		{
			ChangeButtonPosition(Input::MouseDeltaX);
			std::cout << "마우스 버튼 클릭 감지" << std::endl;
			//if(Input::MouseDeltaX != 0.0f)
			//{
			//	
			//	/*onClickEvent.Invoke();*/
			//}
		}
	}
	else OnButton = false;
	
	if (IsMouseOverBackground(mouseVec) && !OnButton)
	{
		std::cout << "마우스 게이지 배경 지나감 감지" << std::endl;
		if (Input::leftButtonDown)
		{
			std::cout << "마우스 배경 클릭 감지" << std::endl;
			/*ChangeButtonPosition();*/
			/*onClickEvent.Invoke();*/
		}
	}
}

