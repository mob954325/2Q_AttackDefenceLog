#pragma once
#include "Components/UI/UIComponent.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Components/Collision/AABBCollider.h"
#include <Utils/EventDelegate.h>
#include <string>
#include <functional>

/// 25.07.29 | 작성자 : 이성호
/// 버튼 UI 컴포넌트로 누름, 땜 이미지 설정 가능
/// 외부의 Input 변수로 마우스 이벤트 감지하고 있음
/// NOTE: 현재 Button에서만 mouse 이벤트 받고 있음 -> 부모에서 뿌릴 수 있게 리펙토링 고려해보기

class Button : public UIComponent
{
public:
	void OnCreate() override;
	void OnStart() override;
	void Update() override;
	void SetNormalImage(std::wstring path);
	BitmapRenderer* GetNormalImage();
	void SetPressedImage(std::wstring path);
	BitmapRenderer* GetPressedImage();
	void SetRect(float width, float height);

	void SetOnClickEvent(std::function<void()> cb);

	bool IsMouseOver(const Vector2& mousePos) const;
	
private:
	BitmapRenderer* normal{};
	BitmapRenderer* pressed{};

	D2D1_RECT_F screenRect{};

	// EventDelegate<> onClickEvent;
};

