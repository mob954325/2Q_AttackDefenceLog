#include "Button.h"
#include "Components/Base/GameObject.h"
#include "Platform/Input.h"
#include "Datas/EngineData.h"

void Button::OnCreate()
{

}

void Button::OnStart()
{
	normal = owner->AddComponent<BitmapRenderer>();
	pressed = owner->AddComponent<BitmapRenderer>();

	normal->CreateBitmapResource(L"../../Resource/UI/Test_Button/button_square.png");
	// normal->SetActive(false);

	pressed->CreateBitmapResource(L"../../Resource/UI/Test_Button/button_square_pressed.png");
	pressed->SetActive(false);

	SetOnClickEvent(NULL); // 0730 : Test code
}

void Button::Update()
{
	// check mouse position
	Vector2 mouseVec = { Input::MouseX, Input::MouseY };

	if (IsMouseOver(mouseVec))
	{
		normal->SetActive(false);
		pressed->SetActive(true);


		if (Input::leftButtonDown || Input::middleButtonDown || Input::rightButtonDown)
		{
			std::cout << "==== 마우스 클릭 =====" << std::endl;
			onClickEvent.Invoke(); // NOTE: 버튼 이벤트 등록 및 실행할 수 있게되면 이 주석 제거하기
		}
	}
	else
	{
		normal->SetActive(true);
		pressed->SetActive(false);
	}
}

void Button::SetNormalImage(std::wstring path)
{
	normal->CreateBitmapResource(path);
}

BitmapRenderer* Button::GetNormalImage()
{
	return normal;
}

void Button::SetPressedImage(std::wstring path)
{
	pressed->CreateBitmapResource(path);
}

BitmapRenderer* Button::GetPressedImage()
{
	return pressed;
}

void Button::SetRect(float width, float height)
{
	Vector2 position = owner->GetTransform().GetPosition();
	if (owner->GetTransform().IsUnityCoords())
	{
		screenRect = {position.x, position.y, position.x + width, position.y + height};
		screenRect.left += EngineData::SceenWidth / 2;
		screenRect.right += EngineData::SceenWidth / 2;
		screenRect.top += EngineData::SceenHeight / 2;
		screenRect.bottom += EngineData::SceenHeight / 2;
	}
	else
	{
		screenRect = {position.x, position.y, position.x + width, position.y + height};
	}
}

void Button::SetOnClickEvent(std::function<void()> cb)
{
	int id = onClickEvent.Add([]() {std::cout << "버튼 이벤트 확인 " << std::endl; }); 
}

bool Button::IsMouseOver(const Vector2& mousePos) const
{
	return mousePos.x >= screenRect.left && // 왼쪽
		mousePos.x <= screenRect.right &&	// 오른쪽 
		mousePos.y >= screenRect.top &&		// 위
		mousePos.y <= screenRect.bottom;	// 아래
}
