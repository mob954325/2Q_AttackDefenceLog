# D2DRenderManager

---

경로 : Platform/D2DRenderManager

## 설명

RenderComponent를 상속받은 컴포넌트들이 사용할 수 있는 DirectX11 2D 기능이 모여있는 클래스

## 예시 코드

```cpp
void BitmapRenderer::Render(D2DRenderManager* manager)
{
	if (!IsActiveSelf()) return;

	if (m_bitmapResource != nullptr)
	{
		D2D1_MATRIX_3X2_F mat = owner->GetTransform().GetFinalMatrix();
		
		if (isFlip) mat.m11 = -mat.m11;

		manager->SetBitmapTransform(mat);
		manager->DrawBitmap(m_bitmapResource->GetBitmap());
	}
}
```

## 멤버 함수

| 이름 | 내용 |
| --- | --- |
| Initialize | Application에서 호출 | 해당 클래스가 사용하는 객체를 생성하는 함수 |
| Uninitialize | Application에서 호출 | 생성한 객체 정리하는 함수 |
| Render | Application에서 호출 |  RenderSystem Update을 매 프레임 호출하는 함수 |
| SetD2D1DeviceContext7 | Application에서 호출 |  D2D1DeviceContext7 참조하는 함수 |
| SetRenderTransform |  Draw함수 호출 전 호출 | RenerComponent들이 출력할 위치를 설정하는 함수 |
| DrawBitmap | ID2D1Bitmap1을 그리는 함수 |
| CreateBrush | Brush 개체 생성 함수 |
| DrawRectangle | Rect값에 따라 빈 사각형 그리는 함수 |
| DrawCircle | Radius값에 따라 빈 원을 그리는 함수 |
| ~~DrawImage~~ |  |

## 멤버 변수

| 이름 | 내용 |
| --- | --- |
| m_wicImagingFactory | IWICImagingFactory 개체 |
| m_d2dDeviceContext | Appliaction에서 생성한 ID2D1DeviceContext7를 참조하는 변수 |
| m_pDWriteFactory | IDWriteFactory 개체  |
| m_pDWriteTextFormat | IDWriteTextFormat 개체 |
| m_pBrush | ID2D1SolidColorBrush 개체 |