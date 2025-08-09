#include "AppEx.h"
#include "Systems/AudioSystem.h"
#include "Components/Logic/InputSystem.h"
#include "Scene/SceneManager.h"
#include "Scene/TestScene.h"
#include "Resources/Loaders/CsvLoader.h"
#include "Application/AppPaths.h"


void AppEx::Initialize()
{
	__super::Initialize();

	//Scene등록하는거
	testScene = new TestScene::TestScene();
	Singleton<SceneManager>::GetInstance().AddScene(testScene);
	Singleton<SceneManager>::GetInstance().Init();
	//

	//오디오시스템(싱글톤)에 사용할 모든 음원리소스 등록단계
	LoadCSV<SoundResource>::SetCSV(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/DataTable/AllSoundList.csv", soundList);
	AudioSystem::GetInstance().Initialize(128);
	AudioSystem::GetInstance().Register(soundList);

	//마우스 이미지 등록(클릭이미지, 평소 이미지)
	hCursorDefault = mouse.LoadPngCursor(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/UI/TestMouse/idle.png");
	hCursorClicked = mouse.LoadPngCursor(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/UI/TestMouse/click.png");
}

//게임종료시 해제할것들
void AppEx::Uninitialize()
{
	AudioSystem::GetInstance().UnRegister();
	__super::Uninitialize();
}

//App을 상속받았을때 아래와 같이 구현해야 마우스가 변경됨
void AppEx::MessageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

