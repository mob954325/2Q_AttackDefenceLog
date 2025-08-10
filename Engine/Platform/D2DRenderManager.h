#pragma once
#include "framework.h"
#include "Components/Base/Transform.h"
#include "Components/Rendering/RenderComponent.h" 

using namespace Microsoft::WRL;

class RenderSystem;
// Direct2D 코드 재활용 하기 위한 클래스 | IRenderer
class D2DRenderManager 
{
public:
	void Initialize();
	void Uninitialize();
	void Render();

	void SetD2D1DeviceContext7(ID2D1DeviceContext7* pD2D1DeviceContext7);
	void SetD2D8Factory(ID2D1Factory8* pD2D1Factory);

	void SetRenderTransform(D2D1_MATRIX_3X2_F& finalMatrix);
	void DrawBitmap(ComPtr<ID2D1Bitmap1> bitmap);
	void DrawBitmap(ComPtr<ID2D1Bitmap1> bitmap, D2D1_RECT_F& destRect, D2D1_RECT_F& srcRect);
	void DrawBitmap(ComPtr<ID2D1Bitmap1> bitmap, D2D1_RECT_F& destRect, D2D1_RECT_F& srcRect, float capacity);
	void DrawImage(ComPtr<ID2D1Effect> effect);

	void CreateBrush(const D2D1::ColorF& color, ID2D1SolidColorBrush** pBrush);
	void DrawRectangle(D2D1_RECT_F& rect, ID2D1Brush* brush, FLOAT width = 1.0f, ID2D1StrokeStyle* strokeStyle = (ID2D1StrokeStyle*)0);
	void DrawCircle(ID2D1Brush* brush, FLOAT radius = 1.0f, FLOAT width = 1.0f, ID2D1StrokeStyle* strokeStyle = (ID2D1StrokeStyle*)0);
	void DrawLine(ID2D1Brush* brush, D2D1_POINT_2F p1, D2D1_POINT_2F p2, FLOAT width = 1.0f, ID2D1StrokeStyle* strokeStyle = (ID2D1StrokeStyle*)0);
	void DrawLine(ID2D1Brush* brush, Vector2 p1, Vector2 p2, FLOAT width = 1.0f, ID2D1StrokeStyle* strokeStyle = (ID2D1StrokeStyle*)0);

	/// <summary>
	/// WIC를 통해 이미지를 ID2D1Bitmap1**로 반환하는 함수
	/// </summary>
	/// <param name="path">이미지 경로</param>
	/// <param name="outBitmap">반환 될 Bitmap</param>
	/// <returns>상태</returns>
	HRESULT CreateBitmapFromFile(const wchar_t* path, ID2D1Bitmap1** outBitmap);
	void PrintText(const wchar_t* str, float left, float top, bool isWorld = false);
	void PrintText(const wchar_t* str, float left, float top, D2D1::ColorF color, bool isWorld = false);
	// void CreateEffect(ID2D1Effect** skew, ID2D1Effect** shadow, Microsoft::WRL::ComPtr<ID2D1Bitmap> bitmap);
	void CreateVignetteEffect(ID2D1Effect** pVignette);

	void CreatePathGeometry(ID2D1PathGeometry** pPath);
	void CreateLayer(ID2D1Layer** pLayer, D2D1_SIZE_F* size = NULL);
	void PushLayer(const D2D1_RECT_F& contentSize, ID2D1Geometry* geomatry, ID2D1Layer* pLayer);
	void PopLayer();

	void SetAntialiasMode(D2D1_ANTIALIAS_MODE mode = D2D1_ANTIALIAS_MODE_ALIASED);
	void CreateSpriteBatch(ID2D1SpriteBatch** batch);
	void DrawSpriteBatch(ID2D1SpriteBatch* spriteBatch, UINT32 startIndex, UINT32 spriteCount, ComPtr<ID2D1Bitmap1> bitmap, 
		D2D1_BITMAP_INTERPOLATION_MODE interpolation = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1_SPRITE_OPTIONS spriteOption = D2D1_SPRITE_OPTIONS_NONE);

protected:
	ComPtr<IWICImagingFactory> m_wicImagingFactory;
	ComPtr<ID2D1DeviceContext7> m_d2dDeviceContext;
	ComPtr<ID2D1Factory8> m_d2d1Factory8;

	// DWrite
	ComPtr<IDWriteFactory> m_pDWriteFactory;
	ComPtr<IDWriteTextFormat> m_pDWriteTextFormat;
	ComPtr<ID2D1SolidColorBrush> m_pBrush; // 브러시 개체 인터페이스 포인터 변수
};