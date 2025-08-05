#include "SliceRenderer.h"
#include "Components/Base/GameObject.h"
#include "Platform/D2DRenderManager.h"
#include "Resources/ResourceManager.h"

void SliceRenderer::OnCreate()
{
}

void SliceRenderer::OnStart()
{
	HRESULT hr = S_OK;
	//hr = renderManager->GetFactory()->CreatePathGeometry(&pathGeometry1);
	assert(SUCCEEDED(hr) && " fail create pathGeometry1");

	//hr = renderManager->GetFactory()->CreatePathGeometry(&pathGeometry2);
	assert(SUCCEEDED(hr) && " fail create pathGeometry2");
}

void SliceRenderer::OnDestroy()
{
	if (slice1) slice1.Reset(); // TODO : 나중에 해제 제대로 되는지 확인할 것
	if (slice2) slice2.Reset();
}

void SliceRenderer::Render(D2DRenderManager* manager)
{
	if (!IsActiveSelf()) return;

	D2D1_MATRIX_3X2_F fmat = owner->GetTransform().GetFinalMatrix();
	D2D1_MATRIX_3X2_F fmat1 = fmat;
	D2D1_MATRIX_3X2_F fmat2 = fmat;

}

void SliceRenderer::SetOriginal(std::wstring path)
{
	if (originBitmap)
	{
		originBitmap.reset();
	}

	originBitmap = resourceManager->CreateBitmapResource(path);
}

void SliceRenderer::Slice(const Vector2& dirVec)
{
	assert(originBitmap && "originalBitmap is emtpy.");

	// NOTE : 단일 이미지 기준 작성
	D2D1_SIZE_F size = originBitmap->GetBitmap()->GetSize();
	D2D1_POINT_2U destPoint = { 0,0 };
	D2D1_RECT_U srcRect = { 0,0, size.width, size.height };
	slice1 = originBitmap->GetBitmap();
	slice2 = originBitmap->GetBitmap();

	// test code
	slice1Info = { {200,200}, D2D1::Matrix3x2F::Identity(), 1 };
	slice2Info = { {200,200 - 20}, D2D1::Matrix3x2F::Identity(), 1 };
}

void SliceRenderer::Reset()
{
}
