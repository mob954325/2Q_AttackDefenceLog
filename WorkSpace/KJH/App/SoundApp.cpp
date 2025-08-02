#include "SoundApp.h"
#include "Systems/AudioSystem.h"
#include "Components/Logic/InputSystem.h"
#include "Scene/SceneManager.h"
#include "Scene/TestScene.h"


void SoundApp::SoundApp::Initialize()
{
	//WCHAR buffer[MAX_PATH];
	//GetCurrentDirectory(MAX_PATH, buffer);
	//MessageBox(NULL, buffer, L"현재 작업 디렉터리", MB_OK);

	/*WCHAR buffer[MAX_PATH];
	GetFullPathName(L"../../Resource/UI/TestMouse/idle.png", MAX_PATH, buffer, nullptr);
	MessageBox(NULL, buffer, L"실제 시도 중인 파일 경로", MB_OK);*/


	__super::Initialize();

	testScene = new TestScene::TestScene();
	Singleton<SceneManager>::GetInstance().AddScene(testScene);
	Singleton<SceneManager>::GetInstance().Init();
	AudioSystem::GetInstance().Initialize(128);
	AudioSystem::GetInstance().Register(musiclist);


	hCursorDefault = mouse.LoadPngCursor(L"../../Resource/UI/TestMouse/idle.png");
	hCursorClicked = mouse.LoadPngCursor(L"../../Resource/UI/TestMouse/click.png");


	//if (!hCursorDefault)
	//	MessageBox(0, L"기본 커서 로딩 실패", L"Error", MB_OK);
	//if (!hCursorClicked)
	//	MessageBox(0, L"click 커서 로딩 실패", L"Error", MB_OK);
}

void SoundApp::SoundApp::Uninitialize()
{
	AudioSystem::GetInstance().UnRegister();
	__super::Uninitialize();
}

void SoundApp::SoundApp::MessageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//if (msg == WM_EXITSIZEMOVE)
	//{
	//	MessageBox(NULL, L"WM_EXITSIZEMOVE 도착", L"Debug", MB_OK);
	//}

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
		/*return TRUE;*/
	default:
		////Windows에서는 메시지를 직접 처리하지 않는 경우, 운영체제의 기본 처리로 넘겨야 함.
		//return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}
}
