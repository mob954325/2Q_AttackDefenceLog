#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/UI/Button.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Components/Logic/InputSystem.h"

/* 25.08.09 | 작성자: 이성호
*  esc메뉴의 모든 버튼 관리 스크립트 
	씬에서 반드시 SetButtons와 SetButtonsPosition을 통해 등록 및 위치 지정을 해줄 것
*/

class StageESCPanel : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;

	void SetButtons(const std::vector<GameObject*> buttons);
	void SetButtonsPosition();
	void DisablePanel();
	void EnablePanel();

	void SetInputEnable(bool value);

private:
	BitmapRenderer* backgroundBitmap{};
	BitmapRenderer* barBitmap{};
	InputSystem* input;

	std::vector<GameObject*> buttons; // 순서대로 continue, exit, mute
	bool isInputEnable = false;
};

