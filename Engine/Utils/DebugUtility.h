#pragma once
#include "pch.h"
#include "Utils/Singleton.h"

/// <summary>
/// 디버그용 기능 함수 모음 클래스
/// </summary>
class DebugUtility : public Singleton<DebugUtility>
{
public:
	friend class Singleton<DebugUtility>;

	void GetDxgiAdapter(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice);

	std::string FormatBytes(UINT64 bytes);
	void PrintMemoryUsage();
	static void Print(std::wstring str);
	static void Print(std::string str);
	void UpdateFPSCount();
	int GetFPSCount();

private:
	DebugUtility() = default;
	~DebugUtility() = default;

	Microsoft::WRL::ComPtr<IDXGIAdapter3> dxgiAdapter;

	const float fpsMaxTime = 1.0f;
	float fpsTimer = 0.0f;
	int cachedFpsCount = 0;
	int fpsCount = 0;
};