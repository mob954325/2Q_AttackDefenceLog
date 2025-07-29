#include <windows.h>
#include "LogicTestApplication/LogicTestApplication.h"
#include <io.h>
#include <fcntl.h>


// ASB

/// <summary>
/// 프로그램 winMain
/// </summary>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    CoInitialize(nullptr);  // COM 초기화
	AllocConsole();

	// 표준 출력 리디렉션
	FILE* fp;
    
    errno_t err1 = freopen_s(&fp, "CONOUT$", "w", stdout); // std::cout
    errno_t err2 = freopen_s(&fp, "CONOUT$", "w", stderr); // std::cerr
    errno_t err3 = freopen_s(&fp, "CONIN$", "r", stdin);   // std::cin
	if (err1 != 0) {MessageBoxW(nullptr, L"freopen_s 실패", L"Error", MB_OK);}
	if (err2 != 0) {MessageBoxW(nullptr, L"freopen_s 실패", L"Error", MB_OK);}
	if (err3 != 0) {MessageBoxW(nullptr, L"freopen_s 실패", L"Error", MB_OK);}
	


	std::cout << "콘솔 출력 테스트 - 한글" << std::endl;
    std::cout.flush();
	//MessageBoxW(nullptr, L"GUI 창입니다.", L"WinMain", MB_OK);


    // app.Initialize();
    // app.Run();
    // app.Uninitialize();
    LogicTestApplication TestApplication;
    TestApplication.Initialize();
    TestApplication.Update();
    TestApplication.Render();
    TestApplication.Uninitialize();

    FreeConsole(); // 필요 없으면 종료 시 콘솔 제거
    CoUninitialize();        // COM 해제
    return (int)1;
}