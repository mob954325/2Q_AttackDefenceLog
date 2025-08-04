#include "pch.h"
#include "D2DRenderManager.h"
#include "Utils/Singleton.h"
#include "Systems/RenderSystem.h"

void D2DRenderManager::Initialize()
{
	HRESULT hr;

	// Create WIC factory
	hr = CoCreateInstance(CLSID_WICImagingFactory,
		NULL, CLSCTX_INPROC_SERVER,
		__uuidof(m_wicImagingFactory),
		(void**)m_wicImagingFactory.GetAddressOf());

	assert(SUCCEEDED(hr));

	// DirectWrite 팩터리를 만듭니다.
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_pDWriteFactory), reinterpret_cast<IUnknown**>(m_pDWriteFactory.GetAddressOf()));
	assert(SUCCEEDED(hr));

	// DirectWrite 텍스트 형식 개체를 만듭니다.
	hr = m_pDWriteFactory->CreateTextFormat(
		L"", // FontName    제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		15.0f,   // Font Size
		L"", //locale
		&m_pDWriteTextFormat
	);
	assert(SUCCEEDED(hr));
}

void D2DRenderManager::Uninitialize()
{
	m_wicImagingFactory = nullptr;
}

void D2DRenderManager::Render()
{
	assert(m_d2dDeviceContext);

	m_d2dDeviceContext->BeginDraw();

	// Clear
	m_d2dDeviceContext->Clear(D2D1::ColorF(D2D1::ColorF::DarkSlateBlue));

	Singleton<RenderSystem>::GetInstance().Update(this);

	HRESULT hr = m_d2dDeviceContext->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		std::cout << "D2DERR_RECREATE_TARGET" << std::endl;
	}
}

void D2DRenderManager::SetD2D1DeviceContext7(ID2D1DeviceContext7* pD2D1DeviceContext7)
{
	if (pD2D1DeviceContext7)
	{
		m_d2dDeviceContext = pD2D1DeviceContext7;

		// Brush 생성
		HRESULT hr = m_d2dDeviceContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::GreenYellow), &m_pBrush);
		assert(SUCCEEDED(hr));
	}
}

void D2DRenderManager::SetD2D8Factory(ID2D1Factory8* pD2D1Factory)
{
	m_d2d1Factory8 = pD2D1Factory;
}

ComPtr<ID2D1Factory8> D2DRenderManager::GetFactory()
{
	return m_d2d1Factory8;
}

void D2DRenderManager::SetRenderTransform(D2D1_MATRIX_3X2_F& finalMatrix)
{
	m_d2dDeviceContext->SetTransform(finalMatrix); // NOTE: Direct2D가 이후에 그릴 모든 도형/텍스트/이미지 등에 적용활 좌표 변환 행렬 설정 함수
}

void D2DRenderManager::DrawBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap)
{
	m_d2dDeviceContext->DrawBitmap(bitmap.Get());
}

void D2DRenderManager::DrawBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap, D2D1_RECT_F& destRect, D2D1_RECT_F& srcRect) 
{
	m_d2dDeviceContext->DrawBitmap(bitmap.Get(), &destRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcRect);
}

void D2DRenderManager::DrawBitmap(ComPtr<ID2D1Bitmap1> bitmap, D2D1_RECT_F& destRect, D2D1_RECT_F& srcRect, float capacity)
{
	m_d2dDeviceContext->DrawBitmap(bitmap.Get(), &destRect, capacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcRect);
}

void D2DRenderManager::DrawImage(Microsoft::WRL::ComPtr<ID2D1Effect> effect)
{
	m_d2dDeviceContext->DrawImage(effect.Get());
}

void D2DRenderManager::CreateBrush(const D2D1::ColorF& color, ID2D1SolidColorBrush** pBrush)
{
	m_d2dDeviceContext->CreateSolidColorBrush(color, pBrush);
}

void D2DRenderManager::DrawRectangle(D2D1_RECT_F& rect, ID2D1Brush* brush, FLOAT width, ID2D1StrokeStyle* strokeStyle)
{
	m_d2dDeviceContext->DrawRectangle(rect, brush, width, strokeStyle);
}

void D2DRenderManager::DrawCircle(ID2D1Brush* brush, FLOAT radius, FLOAT width, ID2D1StrokeStyle* strokeStyle)
{
	m_d2dDeviceContext->DrawEllipse({{0, 0}, radius, radius}, brush, width, strokeStyle); // NOTE: 만약 타원이 필요하면 raidus를 쪼개면 됨., 위치가 0인 이유는 SetTransform으로 위치를 옮기기 때문
}

void D2DRenderManager::DrawLine(ID2D1Brush* brush, D2D1_POINT_2F p1, D2D1_POINT_2F p2, FLOAT width, ID2D1StrokeStyle* strokeStyle)
{
	m_d2dDeviceContext->DrawLine(p1, p2, brush, width, strokeStyle);
}

void D2DRenderManager::DrawLine(ID2D1Brush* brush, Vector2 p1, Vector2 p2, FLOAT width, ID2D1StrokeStyle* strokeStyle)
{
	D2D1_POINT_2F d2dpoint1 = { p1.x, p1.y };
	D2D1_POINT_2F d2dpoint2 = { p2.x, p2.y };
	DrawLine(brush, d2dpoint1, d2dpoint2, width, strokeStyle);
}

void D2DRenderManager::PrintText(const wchar_t* str, float left, float top, bool isWorld)
{
	if (!m_d2dDeviceContext || !m_pBrush) return;

	if(!isWorld) m_d2dDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());

	m_pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	m_d2dDeviceContext->DrawTextW(str, (UINT32)wcslen(str), m_pDWriteTextFormat.Get(), D2D1::RectF(left, top, left + 300, top + 250), m_pBrush.Get());
}

void D2DRenderManager::PrintText(const wchar_t* str, float left, float top, D2D1::ColorF color, bool isWorld)
{
	if (!m_d2dDeviceContext || !m_pBrush) return;

	if (!isWorld) m_d2dDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());

	m_pBrush->SetColor(D2D1::ColorF(color));
	m_d2dDeviceContext->DrawTextW(str, (UINT32)wcslen(str), m_pDWriteTextFormat.Get(), D2D1::RectF(left, top, left + 300, top + 250), m_pBrush.Get());
}

void D2DRenderManager::CreateEffect(ID2D1Effect** skew, ID2D1Effect** shadow, Microsoft::WRL::ComPtr<ID2D1Bitmap> bitmap) // ?
{
	// AffineTransform2D 이펙트 생성	
	HRESULT hr = m_d2dDeviceContext->CreateEffect(CLSID_D2D12DAffineTransform, skew);

	// 반투명 검정색으로 바꾸기 위해 ColorMatrix 사용 (선택적)
	hr = m_d2dDeviceContext->CreateEffect(CLSID_D2D1ColorMatrix, shadow);

	D2D1_MATRIX_3X2_F skewMatrix = {
		1.0f, 0.0f,      // X scale, Y shear
		1.4f, 1.0f,      // X shear, Y scale
		-60.0f, 0.0f       // X, Y translation
	};

	// 이펙트에 입력 이미지와 행렬 설정
	(*skew)->SetInput(0, bitmap.Get());  // 캐릭터 비트맵
	(*skew)->SetValue(D2D1_2DAFFINETRANSFORM_PROP_TRANSFORM_MATRIX, skewMatrix);
	(*skew)->SetValue(D2D1_2DAFFINETRANSFORM_PROP_INTERPOLATION_MODE, D2D1_2DAFFINETRANSFORM_INTERPOLATION_MODE_LINEAR);
	D2D1_MATRIX_5X4_F shadowMatrix = {
		0, 0, 0, 0,  // R
		0, 0, 0, 0,  // G
		0, 0, 0, 0,  // B
		0, 0, 0, 0.5f,  // A (투명도 조절)
		0, 0, 0, 0   // Offset
	};
	(*shadow)->SetInputEffect(0, *skew);
	(*shadow)->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, shadowMatrix);
}

HRESULT D2DRenderManager::CreateBitmapFromFile(const wchar_t* path, ID2D1Bitmap1** outBitmap)
{
	ComPtr<IWICBitmapDecoder>     decoder;
	ComPtr<IWICBitmapFrameDecode> frameIndex;
	ComPtr<IWICFormatConverter>   converter;

	// ① 디코더 생성
	HRESULT hr = m_wicImagingFactory->CreateDecoderFromFilename(
		path, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);
	if (FAILED(hr)) return hr;

	// ② 첫 프레임 얻기
	hr = decoder->GetFrame(0, &frameIndex);
	if (FAILED(hr)) return hr;

	// ③ 포맷 변환기 생성
	hr = m_wicImagingFactory->CreateFormatConverter(&converter);
	if (FAILED(hr)) return hr;

	// ④ GUID_WICPixelFormat32bppPBGRA로 변환
	hr = converter->Initialize(
		frameIndex.Get(),
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);
	if (FAILED(hr)) return hr;

	// ⑤ Direct2D 비트맵 속성 (premultiplied alpha, B8G8R8A8_UNORM)
	D2D1_BITMAP_PROPERTIES1 bmpProps = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_NONE,
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
	);

	// ⑥ DeviceContext에서 WIC 비트맵으로부터 D2D1Bitmap1 생성
	hr = m_d2dDeviceContext->CreateBitmapFromWicBitmap(converter.Get(), &bmpProps, outBitmap);

	return hr;
}
