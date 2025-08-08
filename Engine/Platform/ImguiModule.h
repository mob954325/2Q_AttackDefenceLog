#pragma once
#include "External/Imgui/imgui.h"

/* 25.08.08 : 작성자 이성호
* Imgui 내용을 정의하는 클래스
*/

class ImguiModule
{
public:
	virtual void ImguiRender() = 0;
};

