#pragma once
#include "Application/Application.h"
#include "Scene/Scene.h"
#include "Datas/SoundDatas.h"
#include <vector>
#include "Utils/HCURSORChange.h"

class AppEx : public Application
{
public:
	void Initialize() override;
	void Uninitialize() override;

	void CALLBACK MessageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

private:
	Scene* testScene{};

	std::vector<SoundResource> soundList;

	HCURSORChange mouse;

	HCURSOR hCursorDefault;
	HCURSOR hCursorClicked;

	bool isMousePressed = false;
};

