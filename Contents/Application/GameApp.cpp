#include "GameApp.h"
#include "Scene/SceneManager.h"

#include "Scenes/TitleScene.h"
#include "Scenes/MenuScene.h"
#include "Scenes/SelectScene.h"
#include "Scenes/EndScene.h"

#include "Scenes/Stage1.h"
#include "Scenes/Stage2.h"
#include "Scenes/Stage3.h"

#include "Systems/AudioSystem.h"
#include "Components/Logic/InputSystem.h"
#include "Resources/Loaders/CsvLoader.h"
#include "Application/AppPaths.h"
#include <windows.h>

void GameApp::Initialize()
{
	__super::Initialize();

	// 	enum SceneCount { << SceneCore 내부에 정의됨
	// 		TITLE = 0,    << 순서 맞춰서 AddScene해주세오
	// 		MENU = 1,
	// 		SELECT = 2,
	// 		END = 3,
	// 		STAGE1 = 4,
	// 		STAGE2 = 5,
	// 		STAGE3 = 6
	// 	};

		// 여기에 씬 추가 및 Init 함수 추가
	titleScene = new TitleScene();		Singleton<SceneManager>::GetInstance().AddScene(titleScene);
	menuScene = new MenuScene();		Singleton<SceneManager>::GetInstance().AddScene(menuScene);
	selectScene = new SelectScene();	Singleton<SceneManager>::GetInstance().AddScene(selectScene);
	endScene = new EndScene();			Singleton<SceneManager>::GetInstance().AddScene(endScene);
	stage1 = new Stage1();				Singleton<SceneManager>::GetInstance().AddScene(stage1);
	stage2 = new Stage2();				Singleton<SceneManager>::GetInstance().AddScene(stage2);
	stage3 = new Stage3();				Singleton<SceneManager>::GetInstance().AddScene(stage3);


	LoadCSV<SoundResource>::SetCSV(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\DataTable\\AllSoundList.csv", soundList);
	AudioSystem::GetInstance().Initialize(4090);
	AudioSystem::GetInstance().Register(soundList);




	hCursorDefault = mouse.LoadPngCursor((Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\Mouse\\mouse_cursor_1.png").c_str());
	hCursorClicked = mouse.LoadPngCursor((Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\Mouse\\mouse_cursor_2.png").c_str());

	if (!hCursorDefault)
		MessageBox(0, L"기본 커서 로딩 실패", L"Error", MB_OK);
	if (!hCursorClicked)
		MessageBox(0, L"click 커서 로딩 실패", L"Error", MB_OK);

	Singleton<SceneManager>::GetInstance().Init();
}

void GameApp::Uninitialize()
{
	AudioSystem::GetInstance().UnRegister();
	__super::Uninitialize();
}

void GameApp::MessageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Application::MessageProc(hWnd, msg, wParam, lParam); // 부모 호출

	switch (msg)
	{
	case WM_LBUTTONDOWN:
		isMousePressed = true;
		SetCursor(hCursorClicked);
		break;
	case WM_LBUTTONUP:
		isMousePressed = false;
		SetCursor(hCursorDefault);
		break;
	case WM_SETCURSOR:
		SetCursor(isMousePressed ? hCursorClicked : hCursorDefault);
	default:
		break;
	}
}
