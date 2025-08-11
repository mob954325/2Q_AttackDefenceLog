#include "SoundApp.h"
#include "Systems/AudioSystem.h"
#include "Components/Logic/InputSystem.h"
#include "Scene/SceneManager.h"
#include "Scene/TestScene.h"
#include "Resources/Loaders/CsvLoader.h"
#include "Application/AppPaths.h"


void SoundApp::SoundApp::Initialize()
{
	//WCHAR buffer[MAX_PATH];
	//GetCurrentDirectory(MAX_PATH, buffer);
	//MessageBox(NULL, buffer, L"현재 작업 디렉터리", MB_OK);

	/*WCHAR buffer[MAX_PATH];
	GetFullPathName(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/UI/TestMouse/idle.png", MAX_PATH, buffer, nullptr);
	MessageBox(NULL, buffer, L"실제 시도 중인 파일 경로", MB_OK);*/

	__super::Initialize();
	std::wstring path = Singleton<AppPaths>::GetInstance().GetWorkingPath();
	LoadCSV<SoundResource>::SetCSV(path + L"\\..\\Resource\\DataTable\\AllSoundList.csv", soundList);

	// 출력 테스트
	//for (const auto& sound : soundList) {
	//	std::wcout /*<< L"[ID] " << sound.id*/
	//		<< L", [Path] " << sound.path
	//		/*<< L", [Mode] " << sound.mode*/
	//		<< std::endl;
	//}

	testScene = new TestScene::TestScene();
	Singleton<SceneManager>::GetInstance().AddScene(testScene);
	Singleton<SceneManager>::GetInstance().Init();
	AudioSystem::GetInstance().Initialize(128);
	AudioSystem::GetInstance().Register(soundList);


	std::wstring mouseIdleIcon = Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\TestMouse\\idle.png";
	std::wstring mouseClickIcon = Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\TestMouse\\click.png";
	hCursorDefault = mouse.LoadPngCursor(mouseIdleIcon.c_str());
	hCursorClicked = mouse.LoadPngCursor(mouseClickIcon.c_str());


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

	//switch (msg)
	//{
	//case WM_LBUTTONDOWN:
	//	isMousePressed = true;
	//	SetCursor(hCursorClicked);
	//	break;
	//case WM_LBUTTONUP:
	//	isMousePressed = false;
	//	SetCursor(hCursorDefault);
	//	break;
	//case WM_SETCURSOR:
	//	SetCursor(isMousePressed ? hCursorClicked : hCursorDefault);
	//	/*return TRUE;*/
	//default:
	//	////Windows에서는 메시지를 직접 처리하지 않는 경우, 운영체제의 기본 처리로 넘겨야 함.
	//	//return DefWindowProc(hWnd, msg, wParam, lParam);
	//	break;
	//}
}
