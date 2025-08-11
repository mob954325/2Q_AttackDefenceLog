#include "BitmapRenderer.h"
#include "Platform/D2DRenderManager.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Resources/ResourceManager.h"
#include "Components/Camera/Camera.h"
#include "Datas/EngineData.h"
#include "Resources/BitmapResource.h"

void BitmapRenderer::Render(D2DRenderManager* manager)
{
	if (!IsActiveSelf()) return;

	if (m_bitmapResource != nullptr && m_bitmapResource->GetBitmap())
	{
		D2D1_MATRIX_3X2_F mat = owner->GetTransform().GetFinalMatrix();
		
		if (isFlip) mat.m11 = -mat.m11;

		// layer
		if (!points.empty())
		{
			D2D1_MATRIX_3X2_F layerMat = D2D1::Matrix3x2F::Identity();
			manager->SetRenderTransform(layerMat);
			renderManager->CreateLayer(&layer); // 레이어 생성
			renderManager->PushLayer(D2D1::InfiniteRect(), pathGeometry.Get(), layer); // 레이어 추가
		}

		manager->SetRenderTransform(mat);

		if (!useCustomRect)
		{
			D2D1_SIZE_F size = m_bitmapResource->GetBitmap()->GetSize();
			D2D1_RECT_F dest = { 0,0,size.width,size.height };
			D2D1_RECT_F src = { 0,0,size.width,size.height };
			manager->DrawBitmap(m_bitmapResource->GetBitmap(), dest, src, capacity);
		}
		else
		{
			manager->DrawBitmap(m_bitmapResource->GetBitmap(), destRect, srcRect, capacity); // 0730 : 작성자 : 이성호, rect로 직접 수정할 수 있게 코드 추가
		}

		if (!points.empty()) renderManager->PopLayer(); // 레이어 제거
		layer->Release();
		layer = NULL;
	}
	else // 예외 처리
	{
		if (m_bitmapResource == nullptr)
		{
			std::cerr << "[RenderComponent] Failed to render: m_bitmapResource is nullptr." << std::endl;
		}
		else if (m_bitmapResource->GetBitmap() == nullptr)
		{
			std::cerr << "[RenderComponent] Failed to render: m_bitmapResource->GetBitmap() is nullptr." << std::endl;
		}
		else
		{
			std::cerr << "[RenderComponent] Unknown error occurred in rendering." << std::endl;
		}
	}
}

void BitmapRenderer::OnStart()
{

}

void BitmapRenderer::OnDestroy()
{
	m_bitmapResource.reset();
}

void BitmapRenderer::CreateBitmapResource(std::wstring filePath)
{
 	m_bitmapResource = resourceManager->CreateBitmapResource(filePath);
}

std::shared_ptr<BitmapResource> BitmapRenderer::GetResource()
{
	return m_bitmapResource;
}

void BitmapRenderer::SetFlip(bool value)
{
	isFlip = value;
}

void BitmapRenderer::SetUseCustomRect(bool value)
{
	useCustomRect = value;
}

void BitmapRenderer::SetDestRect(const D2D1_RECT_F& rect)
{
	destRect = rect;
}

D2D1_RECT_F BitmapRenderer::GetDestRect() const
{
	return destRect;
}

void BitmapRenderer::SetSrcRect(const D2D1_RECT_F& rect)
{
	srcRect = rect;
}

D2D1_RECT_F BitmapRenderer::GetSrcRect() const
{
	return srcRect;
}

void BitmapRenderer::SetCapacity(float value)
{
	if (value > 1) capacity = 1;
	else if (value < 0) capacity = 0;
	else capacity = value;
}

float BitmapRenderer::GetCapacity()
{
	return capacity;
}

void BitmapRenderer::SetClipingPosition(const std::vector<Vector2>& points)
{
	HRESULT hr = S_OK;

	this->points.clear();

	if (points.size() < 3)
	{
		std::cerr << "[BitmapRenderer] - 전달 받은 위치값이 부족합니다. 최소 3개 이상을 전달해주세요." << std::endl;
		return;
	}

	this->points = points;

	renderManager->CreatePathGeometry(&pathGeometry);
	pathGeometry->Open(&pSink);

	pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

	pSink->BeginFigure
	(
		D2D1::Point2F(points[0].x, points[0].y), 
		D2D1_FIGURE_BEGIN_FILLED
	);

	int size = points.size();
	for (int i = 1; i < size; i++)
	{
		pSink->AddLine(D2D1::Point2F(points[i].x, points[i].y));
	}

	pSink->EndFigure(D2D1_FIGURE_END_CLOSED);

	hr = pSink->Close();
	assert(SUCCEEDED(hr));
	pSink->Release();
	pSink = nullptr;
}