#include "ImguiManager.h"

void ImguiManager::Init(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	IMGUI_CHECKVERSION(); // 버전 체크?
	ImGui::CreateContext();
	io = ImGui::GetIO();

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(device, deviceContext);
}

void ImguiManager::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (auto m : modules)
	{
		m->ImguiRender();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImguiManager::Add(ImguiModule* m)
{
	modules.push_back(m);
}
