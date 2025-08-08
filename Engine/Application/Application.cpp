#include "pch.h"
#include "Application.h"
#include "Datas/EngineData.h"

#include "Scene/SceneManager.h"
#include "Platform/D2DRenderManager.h"
#include "Systems/ScriptSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/TransformSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/PhysicSystem.h"
#include "Components/Camera/CameraManager.h"

#include "Utils/Singleton.h"
#include "Platform/Input.h"
#include "Utils/GameTime.h"
#include "AppPaths.h"
#include "Utils/DebugUtility.h"

#include "Platform/ImguiManager.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Application* pThis = nullptr;

	// WM_NCCREATE: 윈도우 생성 아주 초기에, 프레임 생성 전에. WM_CREATE보다 이전에발생
	if (uMsg == WM_NCCREATE)
	{
		// lParam은 CREATESTRUCT* 이다
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		pThis = reinterpret_cast<Application*>(cs->lpCreateParams);

		// HWND에 this 포인터 저장
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
	}
	else {
		// WM_NCCREATE가 아닐 때는 HWND에서 this 포인터를 가져온다
		pThis = reinterpret_cast<Application*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

	if (pThis)
		pThis->MessageProc(hWnd, uMsg, wParam, lParam); // 멤버 함수 호출

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Application::Initialize()
{
	Singleton<AppPaths>::GetInstance().InitPaths();

	// Window 생성
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = m_hInstance;
	wc.lpszClassName = EngineData::WindowName.c_str();
	RegisterClass(&wc);

	SIZE clientSize = { (LONG)EngineData::SceenWidth,(LONG)EngineData::SceenHeight };
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

	m_hwnd = CreateWindowEx(0, 
		EngineData::WindowName.c_str(), EngineData::TitleName.c_str(),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		clientRect.right - clientRect.left, clientRect.bottom - clientRect.top,
		nullptr, nullptr, m_hInstance, this);
	ShowWindow(m_hwnd, SW_SHOW);

	// D3D11 디바이스 생성
	D3D_FEATURE_LEVEL featureLevel;
	D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0 };
	D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT, levels, 1,
		D3D11_SDK_VERSION, m_d3dDevice.GetAddressOf(), &featureLevel, m_d3dDeviceContext.GetAddressOf());

	// D2D 팩토리 및 디바이스 생성
	D2D1_FACTORY_OPTIONS options = {
#ifdef _DEBUG
		D2D1_DEBUG_LEVEL_INFORMATION
#endif // _DEBUG

	};
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, options, m_d2d1Factory.GetAddressOf());

	ComPtr<IDXGIDevice> dxgiDevice;
	m_d3dDevice.As(&dxgiDevice);
	ComPtr<ID2D1Device7> d2dDevice;
	m_d2d1Factory->CreateDevice((dxgiDevice.Get()), d2dDevice.GetAddressOf());
	d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, m_d2dDeviceContext.GetAddressOf());

	ComPtr<IDXGIFactory7> dxgiFactory;
	CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));

	// SwapChain 생성
	DXGI_SWAP_CHAIN_DESC1 scDesc = {};
	scDesc.Width = EngineData::SceenWidth;
	scDesc.Height = EngineData::SceenHeight;
	scDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	scDesc.SampleDesc.Count = 1;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.BufferCount = 2;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	dxgiFactory->CreateSwapChainForHwnd(m_d3dDevice.Get(), m_hwnd, &scDesc, nullptr, nullptr, m_dxgiSwapChain.GetAddressOf());

	// 스왑체인의 백버퍼를 사용하는 D2D1Bitmap1 인터페이스 생성 
	ComPtr<IDXGISurface> backBuffer;
	m_dxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
	D2D1_BITMAP_PROPERTIES1 bmpProps = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(scDesc.Format, D2D1_ALPHA_MODE_PREMULTIPLIED)
	);
	m_d2dDeviceContext->CreateBitmapFromDxgiSurface(backBuffer.Get(), &bmpProps, m_d2dBitmapTarget.GetAddressOf());
	m_d2dDeviceContext->SetTarget(m_d2dBitmapTarget.Get());

	// d3d targetview 만들기
	CreateD3DRenderTargetViewFromSwapChain();

	// D2DManager 초기화
	m_D2DRenderManager = new D2DRenderManager;
	m_D2DRenderManager->Initialize();
	m_D2DRenderManager->SetD2D1DeviceContext7(m_d2dDeviceContext.Get());
	m_D2DRenderManager->SetD2D8Factory(m_d2d1Factory.Get());

	// BitmapResourceManager 초기화
	m_ResourceManager = new BitmapResourceManager(m_D2DRenderManager);

	// RenderSystem  초기화
	Singleton<RenderSystem>::GetInstance().SetD2DRenderManager(m_D2DRenderManager);
	Singleton<RenderSystem>::GetInstance().SetResourceManager(m_ResourceManager);

	// GameTime 초기화
	Singleton<GameTime>::GetInstance().InitTime();

	// DebugUtility 초기화
	Singleton<DebugUtility>::GetInstance().GetDxgiAdapter(m_d3dDevice, dxgiDevice);

	ConsoleInitialize();

#if _DEBUG
	Singleton<ImguiManager>::GetInstance().Init(m_hwnd, m_d3dDevice.Get(), m_d3dDeviceContext.Get());
#endif 
	// -- Application 상속받은 클래스의 Initialize() 실행
}

void Application::Uninitialize()
{
#if _DEBUG
	Singleton<ImguiManager>::GetInstance().Uninitialize();
	m_d3dDeviceContext = nullptr;
	m_d3dTargetView = nullptr;
#endif

	Singleton<SceneManager>::GetInstance().GetCurrentScene()->OnExit();
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->CleanUpDestroyedObjects();

	m_D2DRenderManager->Uninitialize();
	delete m_D2DRenderManager;

	delete m_ResourceManager;
	m_ResourceManager = nullptr;

	m_d3dDevice = nullptr;
	m_dxgiSwapChain = nullptr;
	m_d2dDeviceContext = nullptr;
	m_d2dBitmapTarget = nullptr;;

	ConsoleUnInitialize();
}

void Application::MessageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#if _DEBUG
	Singleton<ImguiManager>::GetInstance().WndProcHandler(hWnd, msg, wParam, lParam);
#endif

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		m_isWindowOpen = false;
		break;
	case WM_KEYDOWN:
		break;
	case WM_SIZE:
	{
		if (wParam == SIZE_MINIMIZED)
			break; // 최소화는 무시
		
		UINT width = LOWORD(lParam); // 새 너비
		UINT height = HIWORD(lParam); // 새 높이			
		if (EngineData::SceenWidth != width || EngineData::SceenHeight != height)
		{
			EngineData::SceenWidth = width;
			EngineData::SceenHeight = height;
			m_resized = true;
		}
	}
	break;
	case WM_EXITSIZEMOVE:
		if (m_resized)
		{
			ResizeSwapChainBuffers();
			m_resized = false;
		}
		break;
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
		Input::ProcessMouseMessage(hWnd, msg, wParam, lParam);
		break;
	case WM_MOUSELEAVE:
		Input::ResetMouseOnOutOfBounds();
		break;
	default:
		break;
	}
}

void Application::Render()
{
	m_D2DRenderManager->Render();

	// 반드시 D2D 타겟 해제하고 flush (D2D가 백버퍼 락을 해제하도록)
	m_d2dDeviceContext->SetTarget(nullptr);
	m_d2dDeviceContext->Flush();

	// 2) D3D: RTV를 바인드하고(있다면 VS/PS 상태 등도 설정)
	ID3D11RenderTargetView* rtv = m_d3dTargetView.Get();
	m_d3dDeviceContext->OMSetRenderTargets(1, &rtv, nullptr);

	// 3) ImGui 렌더 (ImguiManager::Render() 안에 ImGui_ImplDX11_RenderDrawData 호출 필요)
#if _DEBUG
	Singleton<ImguiManager>::GetInstance().Render();
#endif

	// 4) Present
	m_dxgiSwapChain->Present(1, 0);

	// 5) D2D 타겟 다시 연결 (다음 프레임 D2D 렌더를 위해)
	m_d2dDeviceContext->SetTarget(m_d2dBitmapTarget.Get());
}

void Application::Update()
{
	std::vector<CollisionInfo> collsioninfos;

	// 1. GameTime, Fps 등 엔진 전역 시스템 
	Singleton<GameTime>::GetInstance().UpdateTime();
	Singleton<DebugUtility>::GetInstance().UpdateFPSCount();

	// 2. 현재 씬이 내부에 MonoBehavior System / Transform System / Collision System 등을 호출
	Scene* currentScene = Singleton<SceneManager>::GetInstance().GetCurrentScene();	
	currentScene->PostUpdate();	// 
	currentScene->FixedUpdate(collsioninfos);	// 물리 , 충돌
	currentScene->Update();						// MonoBehavior / 컴포넌트
	currentScene->LateUpdate();					// 

	// 3. 그외 전역 시스템 ( 씬의 외부 내용 업데이트 )
	// ...

	collsioninfos.clear(); // 임시
}

void Application::Run()
{
	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			Update();
			Render();
			Singleton<CollisionSystem>::GetInstance().CheckPrevPairRemoval();
			Singleton<SceneManager>::GetInstance().GetCurrentScene()->CleanUpDestroyedObjects(); // 06 30 추가 : 모든 루프가 끝나고 오브젝트 제거
			Singleton<SceneManager>::GetInstance().CheckSceneLoad();	// 씬 교체 확인 
			Input::ResetMouseEventFrameState();
		}

	}
}

void Application::ConsoleInitialize()
{
#if _DEBUG
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	SetConsoleTitle(L"윈도우 메세지 콘솔 로그");
	printf("-- 콘솔 로그 시작 --\n\n");
#endif
}

void Application::ConsoleUnInitialize()
{
#if _DEBUG
	// 표준 출력 스트림 닫기
	fclose(stdout);
	// 콘솔 해제
	FreeConsole();
#endif
}

void Application::ResizeSwapChainBuffers()
{
	if (!m_dxgiSwapChain || !m_d2dDeviceContext) return;

	m_d2dDeviceContext->SetTarget(nullptr);
	m_d2dBitmapTarget.Reset();

	// 1. 스왑체인 버퍼 리사이즈
	HRESULT hr = m_dxgiSwapChain->ResizeBuffers(0, EngineData::SceenWidth, EngineData::SceenHeight, DXGI_FORMAT_UNKNOWN, 0);
	if (FAILED(hr))
	{
		// 오류 로그 출력
		return;
	}

	// 2. 백버퍼 다시 얻고 D2D Bitmap 다시 생성
	ComPtr<IDXGISurface> backBuffer;
	m_dxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

	D2D1_BITMAP_PROPERTIES1 bmpProps = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
	);
	m_d2dDeviceContext->CreateBitmapFromDxgiSurface(backBuffer.Get(), &bmpProps, m_d2dBitmapTarget.GetAddressOf());
	m_d2dDeviceContext->SetTarget(m_d2dBitmapTarget.Get());

	// 렌더 매니저에도 다시 설정
	m_D2DRenderManager->SetD2D1DeviceContext7(m_d2dDeviceContext.Get());
}

void Application::CreateD3DRenderTargetViewFromSwapChain()
{
	ComPtr<ID3D11Texture2D> backBufferTex;
	HRESULT hr = m_dxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBufferTex));
	if (FAILED(hr)) return;
	m_d3dDevice->CreateRenderTargetView(backBufferTex.Get(), nullptr, m_d3dTargetView.GetAddressOf());
}