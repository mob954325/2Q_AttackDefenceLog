#include <windows.h>

// HSK

/// <summary>
/// 프로그램 winMain
/// </summary>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    CoInitialize(nullptr);  // COM 초기화

    // app.Initialize();
    // app.Run();
    // app.Uninitialize();

    CoUninitialize();        // COM 해제
    return (int)1;
}