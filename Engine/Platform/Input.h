#pragma once
#include <Windows.h>
#include "Utils/Singleton.h"

enum MouseButton
{
	Left = 0,
	Right = 1,
	Middle = 2
};

class Input
{
public:
	Input() = default;
	~Input() = default;

	void Update();
	bool IsKeyDown(int vKey);
	bool IsKeyPressed(int vKey);
	bool IsKeyReleased(int vKey);

	bool IsMouseDown(MouseButton button);

#pragma region Mouse Event Params
	// 매 프레임 시작시 마우스 이벤트 초기화 함수
	static void ResetMouseEventFrameState();

	// 마우스가 화면밖에 나갔는지 확인하는 함수, 화면밖으로 나가면 모든 버튼 비활성화
	static void ResetMouseOnOutOfBounds();

	// 윈도우 메세지 마우스 이벤트 처리 함수 
	static void ProcessMouseMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	static float MouseX;
	static float MouseY;
	static float MouseDeltaX;
	static float MouseDeltaY;

	static int wheelDelta;

	static bool leftButtonDown;
	static bool rightButtonDown;
	static bool middleButtonDown;

	static bool IsTrackingMouse;
	static bool IsMouseInside;
#pragma endregion

private:
	SHORT prevState[256] = { 0 };
	SHORT currState[256] = { 0 };
};

