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

private:
	BitmapRenderer* bitmap;
	Button* muteButton;
	GameObject* muteButtonObj;
	StageESCPanel* panel;

	std::wstring offUIImagePath;
	std::wstring onUIImagePath;

	bool isPressed = false;
	bool isOpen = false;
	bool isMute = false;
};

