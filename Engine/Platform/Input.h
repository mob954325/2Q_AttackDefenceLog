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

	// 윈도우 메세지 마우스 이벤트 처리 함수
	static void ProcessMouseMessage(UINT message, WPARAM wParam, LPARAM lParam);

	static float MouseX;
	static float MouseY;
	static float MouseDeltaX;
	static float MouseDeltaY;

	static int wheelDelta;

	static bool leftButtonDown;
	static bool rightButtonDown;
	static bool middleButtonDown;
#pragma endregion

private:
	SHORT prevState[256] = { 0 };
	SHORT currState[256] = { 0 };
};

