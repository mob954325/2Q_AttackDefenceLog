#pragma once
#include "pch.h"
#include "Utils/Singleton.h"
#include "External/Imgui/imgui.h"
#include "External/Imgui/imgui_impl_dx11.h"
#include "External/Imgui/imgui_impl_win32.h"
#include "ImguiModule.h"

/// <summary>
/// 디버깅을 위한 시각화 모듈
/// </summary>
class ImguiManager : Singleton<ImguiManager>
{
public:
	void Init(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Render();

	void Add(ImguiModule* m);
private:

	ImGuiIO io{};
	std::vector<ImguiModule*> modules;
};