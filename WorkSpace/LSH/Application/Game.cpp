#include <windows.h>
#include "TestColliderApp/App/TestColliderApp.h"

/// <summary>
/// 프로그램 winMain
/// </summary>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    CoInitialize(nullptr);  // COM 초기화

    // 25.07.28 - 이성호
    // 실행할 Application 클래스 여기에 작성하기
    TestCollider::TestColliderApp app;

    app.Initialize();
    app.Run();
    app.Uninitialize();

    CoUninitialize();        // COM 해제
    return (int)1;
}