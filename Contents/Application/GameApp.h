#pragma once
#pragma once
#include "Application/Application.h"
#include "Scene/Scene.h"
#include "Datas/SoundDatas.h"
#include "../Engine/Utils/HCURSORChange.h"

/* 실제 실행할 게임 App 클래스 | 작성자 : 이성호
* 
*/
class GameApp : public Application
{
public:
	void Initialize() override;
	void Uninitialize() override;
	void CALLBACK MessageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

private:
	// 여기에 Scene 데이터 추가하기
	Scene* titleScene;
	Scene* menuScene;
	Scene* selectScene;
	Scene* endScene;

	Scene* stage1;
	Scene* stage2;
	Scene* stage3;

	std::vector<SoundResource> soundList;

	HCURSORChange mouse;

	HCURSOR hCursorDefault;
	HCURSOR hCursorClicked;

	bool isMousePressed = false;
};