#include "Button.h"
#include "Components/Base/GameObject.h"
#include "Platform/Input.h"
#include "Datas/EngineData.h"
#include "Application/AppPaths.h"

void Button::OnCreate()
{
	normal = owner->AddComponent<BitmapRenderer>();
	hover = owner->AddComponent<BitmapRenderer>();
	pressed = owner->AddComponent<BitmapRenderer>();
}

void Button::OnStart()
{
	normal->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\Test\\Test_Button\\button_square.png");
	normal->SetActive(true);

	hover->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\Test\\Test_Button\\button_square_hover.png");
	hover->SetActive(false);

	pressed->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\Test\\Test_Button\\button_square_pressed.png");
	pressed->SetActive(false);
}

void Button::Update()
{
	if (!IsActiveSelf()) return;

	// check mouse position
	Vector2 mouseVec = { Input::MouseX, Input::MouseY };

	if (IsMouseOver(mouseVec))
	{
		HandleButtonImage(ButtonState::Hover);

		// 마우스 3버튼 아무거나 클릭하면 이벤트 실행
		if (Input::leftButtonDown /*|| Input::middleButtonDown || Input::rightButtonDown*/)
		{
			HandleButtonImage(ButtonState::Pressed);
			onClickEvent.Invoke();
		}
	}
	else
	{
		HandleButtonImage(ButtonState::Normal);
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

void Button::SetHoverImage(std::wstring path)
{
	hover->CreateBitmapResource(path);
}

BitmapRenderer* Button::GetHoverImage()
{
	return hover;
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
		// 유니티 좌표처럼 위치 보정 
		screenRect = {position.x, position.y, position.x + width, position.y + height};
		screenRect.left += EngineData::SceenWidth / 2;
		screenRect.right += EngineData::SceenWidth / 2;
		screenRect.top += EngineData::SceenHeight / 2;
		screenRect.bottom += EngineData::SceenHeight / 2;
	}
	else
	{
		screenRect = {position.x, position.y, position.x + width, position.y + height}; // 좌측 상단을 기준으로 충돌 범위 설정
	}
}

void Button::UseCustomRect(bool value)
{
	useCustomRect = value;
}

void Button::SetCustomRect(D2D1_RECT_F rect)
{
	customRect = rect;
}

size_t Button::AddOnClickEvent(std::function<void()> fn)
{
	int id = onClickEvent.Add(fn); 
	return id; // 이벤트 아이디 반환
}

void Button::RemoveOnClickEventById(size_t id)
{
	onClickEvent.RemoveByID(id);
}


bool Button::IsMouseOver(const Vector2& mousePos) const
{
	if (useCustomRect)
	{
		return mousePos.x >= customRect.left && // 왼쪽
			mousePos.x <= customRect.right &&	// 오른쪽 
			mousePos.y >= customRect.top &&		// 위
			mousePos.y <= customRect.bottom;	// 아래
	}
	else
	{
		return mousePos.x >= screenRect.left && // 왼쪽
			mousePos.x <= screenRect.right &&	// 오른쪽 
			mousePos.y >= screenRect.top &&		// 위
			mousePos.y <= screenRect.bottom;	// 아래
	}
}

void Button::DisableBitmaps()
{
	normal->SetActive(false);
	hover->SetActive(false);
	pressed->SetActive(false);
}

void Button::EnableBitmaps()
{
	normal->SetActive(true);
	hover->SetActive(true);
	pressed->SetActive(true);
}

void Button::HandleButtonImage(ButtonState type)
{
	switch (type)
	{
	case ButtonState::Normal:
		normal->SetActive(true);
		hover->SetActive(false);
		pressed->SetActive(false);
		break;
	case ButtonState::Hover:
		normal->SetActive(false);
		hover->SetActive(true);
		pressed->SetActive(false);
		break;
	case ButtonState::Pressed:
		normal->SetActive(false);
		hover->SetActive(false);
		pressed->SetActive(true);
		break;
	default:
		break;
	}
}