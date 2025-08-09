#pragma once
#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

#include "Application/AppPaths.h"


/* 25.08.01 | 작성자 : 김정현
마우스포인터의 png는 배경의 알파값이 0 이어야함
이미지 파일의 경로는 ../../Resource/UI/TestMouse/idle.png 이런식으로 지정해주면 됨
매개변수중 x,y 스팟은 (0, 0)이면 커서 이미지의 왼쪽 위 모서리가 클릭 지점이 되고
(16, 16)이면 커서 이미지의 가운데쯤을 클릭 지점으로 지정하는 셈 (32x32 이미지 기준)

png파일을 gdi로 읽어와 gdi가 마우스 포인터 이미지로 쓸수있도록 HCURSOR로 변환 후 셋팅

사용방법
HCURSORChange mouse;			: HCURSORChange 변수
HCURSOR hCursorDefault;			: 클릭마우스 이미지를 HCURSOR로 변환하여 저장하는 함수
HCURSOR hCursorClicked;			: 클릭마우스 이미지를 HCURSOR로 변환하여 저장하는 함수
bool isMousePressed = false;	: 마우스의 클릭관련 bool 변수
위의 변수 4개를 Application에서 선언해줘야함

상속받은 app의 init에
hCursorDefault = mouse.LoadPngCursor(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/UI/TestMouse/idle.png");
hCursorClicked = mouse.LoadPngCursor(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/UI/TestMouse/click.png"); 로 png이미지를 HCURSOR로 변환하여 저장

부모의 MessageProc 를 override해야한다
안의 내용에 부모의 Application::MessageProc(hWnd, msg, wParam, lParam);를 호출해야함
그리고 각 클릭에 대한 이미지를 셋팅해주면 됨
예시)*****
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
		//return TRUE;
	default:
		////Windows에서는 메시지를 직접 처리하지 않는 경우, 운영체제의 기본 처리로 넘겨야 함.
		//return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}
*/

class HCURSORChange
{
public:
	// gdi 실행용 변수
	ULONG_PTR gdiplusToken;

	HCURSORChange();
	~HCURSORChange();
	HCURSOR LoadPngCursor(LPCWSTR pngPath, int xHotspot = 0, int yHotspot = 0);
};



