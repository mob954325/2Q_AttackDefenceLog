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
	}
	else
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
