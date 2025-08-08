﻿#pragma once
#include "framework.h"
#include "Platform/D2DRenderManager.h"
#include "Systems/ScriptSystem.h"
#include "Systems/RenderSystem.h"
#include "Resources/ResourceManager.h"

using namespace Microsoft::WRL;

// 윈도우 프로그램 생성 재활용을 위한 클래스
class Application
{
public:
	D2DRenderManager* m_D2DRenderManager{};
	BitmapResourceManager* m_ResourceManager{};

	/// <summary>
	/// D2DRenderManager 초기화
	/// </summary>	
	virtual void Initialize();
	virtual void Uninitialize();

	virtual void CALLBACK MessageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void Render();
	virtual void Update();
	void Run();

protected:
	void ConsoleInitialize();
	void ConsoleUnInitialize();
	void ResizeSwapChainBuffers();
	void CreateD3DRenderTargetViewFromSwapChain();

	ComPtr<ID3D11Device>			m_d3dDevice;
	ComPtr<ID3D11DeviceContext>		m_d3dDeviceContext;
	ComPtr<ID3D11RenderTargetView>	m_d3dTargetView;
	ComPtr<IDXGISwapChain1>			m_dxgiSwapChain;
	ComPtr<ID2D1DeviceContext7>		m_d2dDeviceContext;
	ComPtr<ID2D1Bitmap1>			m_d2dBitmapTarget;
	ComPtr<ID2D1Factory8>			m_d2d1Factory;

private:
	HINSTANCE		m_hInstance{};
	HWND			m_hwnd{};

	bool m_isWindowOpen = false; // 윈도우가 열렸는지 확인하는 변수
	bool m_resized = false;
};
