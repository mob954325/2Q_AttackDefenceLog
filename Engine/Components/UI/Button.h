#pragma once
#include "Components/UI/UIComponent.h"
#include "Components/Rendering/BitmapRenderer.h"
#include <Utils/EventDelegate.h>
#include <string>
#include <functional>

enum ButtonState
{
	Normal = 0,
	Hover,
	Pressed
};

/// 25.07.29 | 작성자 : 이성호
/// 버튼 UI 컴포넌트로 누름, 땜 이미지 설정 가능
/// 외부의 Input 변수로 마우스 이벤트 감지하고 있음
/// NOTE: 현재 Button에서만 mouse 이벤트 받고 있음 -> 부모에서 뿌릴 수 있게 리펙토링 고려해보기
class Button : public UIComponent
{
public:
	void OnStart() override;
	void Update() override;

	void SetNormalImage(std::wstring path);
	BitmapRenderer* GetNormalImage();
	void SetHoverImage(std::wstring path);
	BitmapRenderer* GetHoverImage();
	void SetPressedImage(std::wstring path);
	BitmapRenderer* GetPressedImage();

	void SetRect(float width, float height);

	/// <summary>
	/// 버튼 클릭이벤트 등록함수
	/// </summary>
	/// <param name="cb"><void()형 함수 객체/param>
	size_t AddOnClickEvent(std::function<void()> fn);
	void RemoveOnClickEventById(size_t id);

	bool IsMouseOver(const Vector2& mousePos) const;

	void DisableBitmaps();
	
private:
	void HandleButtonImage(ButtonState type);

	BitmapRenderer* normal{};
	BitmapRenderer* hover{};
	BitmapRenderer* pressed{};

	D2D1_RECT_F screenRect{};

	EventDelegate<> onClickEvent; // void()형만 받는 클릭 이벤트 
};

