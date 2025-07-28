#include "DebugUtility.h"
#include <sstream>
#include <iomanip>
#include <psapi.h>  // GetProcessMemoryInfo, PROCESS_MEMORY_COUNTERS_EX
#pragma comment(lib, "psapi.lib")

#include "GameTime.h"

void DebugUtility::GetDxgiAdapter(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice)
{
	Microsoft::WRL::ComPtr<IDXGIAdapter> tempDxgiAdapter;	

	d3dDevice.As(&dxgiAdapter);
	dxgiDevice->GetAdapter(tempDxgiAdapter.GetAddressOf());
	tempDxgiAdapter.As(&dxgiAdapter);
}

std::string DebugUtility::FormatBytes(UINT64 bytes)
{
	constexpr double KB = 1024.0;
	constexpr double MB = KB * 1024.0;
	constexpr double GB = MB * 1024.0;

	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2);

	if (bytes >= static_cast<UINT64>(GB))
		oss << (bytes / GB) << " GB";
	else if (bytes >= static_cast<UINT64>(MB))
		oss << (bytes / MB) << " MB";
	else if (bytes >= static_cast<UINT64>(KB))
		oss << (bytes / KB) << " KB";
	else
		oss << bytes << " B";

	return oss.str();
}

void DebugUtility::PrintMemoryUsage()
{
#if _DEBUG
	DXGI_QUERY_VIDEO_MEMORY_INFO memInfo = {};
	dxgiAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &memInfo);
	std::cout << "VRAM: " << FormatBytes(memInfo.CurrentUsage) << std::endl;


	HANDLE hProcess = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS_EX pmc;
	pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS_EX);

	// 현재 프로세스의 메모리 사용 정보 조회
	GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	std::cout << "DRAM: " << FormatBytes(pmc.WorkingSetSize) << std::endl;
	std::cout << "PageFile: " << FormatBytes(pmc.PagefileUsage - pmc.WorkingSetSize) << std::endl;
#endif
}

void DebugUtility::Print(std::wstring str)
{
	std::cout << str.c_str() << std::endl;
}

void DebugUtility::Print(std::string str)
{
	std::cout << str << std::endl;
}

void DebugUtility::UpdateFPSCount()
{
	fpsTimer += Singleton<GameTime>::GetInstance().GetDeltaTime();
	cachedFpsCount++;

	if (fpsTimer > fpsMaxTime)
	{
		fpsTimer = 0.0f;
		fpsCount = cachedFpsCount;
		cachedFpsCount = 0;
	}
}

int DebugUtility::GetFPSCount()
{
	return fpsCount;
}
