#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Components/UI/Button.h"
#include "StageESCPanel.h"
#include "Components/UI/Button.h"

class SoundMutePanel : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;

	void SetStageESCPanel(StageESCPanel* pMono);

	void SetOpen(bool value);
	bool IsOpen();

	void MuteEvent();
	bool CheckMouseHoverOnSlider(float x, float y);

private:
	BitmapRenderer* panelBitmap{};
	Button* muteButton{};
	GameObject* muteButtonObj{};
	StageESCPanel* panel{};

	GameObject* sliderButton{};
	BitmapRenderer* sliderButtonBitmap{};

	std::wstring offUIImagePath;
	std::wstring onUIImagePath;

	D2D1_RECT_F soundSliceRect{}; // 음량 조절 슬라이스 감지 범위 rect

	float offsetX = 0;
	float offsetY = 0;

	bool isPressed = false;
	bool isOpen = false;
	bool isMute = false;
};

