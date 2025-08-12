#include "AnimationRenderer.h"
#include "Components/Camera/Camera.h"
#include "Scene/SceneManager.h"

#include "Utils/GameTime.h"
#include "Datas/SpriteDatas.h"
#include "Utils/DebugUtility.h"
#include "Resources/Loaders/SpriteSheetLoader.h"
#include "Resources/Loaders/AnimationClipLoader.h"

void AnimationRenderer::Render(D2DRenderManager* manager)
{
	if (!m_bitmapResource) return;
	if (!IsActiveSelf()) return;

	// 출력할 최종 위치 설정
	D2D1_MATRIX_3X2_F mat = owner->GetTransform().GetFinalMatrix();

	// flips
	if (isFlipX) mat.m11 = -mat.m11;
	if (isFlipY) mat.m22 = -mat.m22;

	// layer
	if (!points.empty())
	{
		D2D1_MATRIX_3X2_F layerMat = D2D1::Matrix3x2F::Identity();
		manager->SetRenderTransform(layerMat);
		renderManager->CreateLayer(&layer); // 레이어 생성
		renderManager->PushLayer(D2D1::InfiniteRect(), pathGeometry.Get(), layer); // 레이어 추가
	}

	// setTransform
	manager->SetRenderTransform(mat);

	// Spirte 정보에 맞게 위치 조정
	destRect = player.GetDestRect();
	srcRect = player.GetSrcRect();

	manager->DrawBitmap(m_bitmapResource.get()->GetBitmap(), destRect, srcRect, capacity);

	// animPlayer update
	player.Update(Singleton<GameTime>::GetInstance().GetDeltaTime());

	// layer 소멸
	if (!points.empty())
	{
		renderManager->PopLayer(); // 레이어 제거
		layer->Release();
		layer = NULL;
	}
}

void AnimationRenderer::CreateBitmapResource(std::wstring filePath)
{
	m_bitmapResource = resourceManager->CreateBitmapResource(filePath);
	player.SetBitmapResource(*m_bitmapResource);
}

void AnimationRenderer::SetSpriteSheet(std::wstring filePath)
{
	player.SetSpriteSheet(filePath);
}

void AnimationRenderer::SetAnimationClip(std::wstring filePath)
{
	player.SetAnimationClip(filePath);
}

AnimationPlayer* AnimationRenderer::GetAnimationPlayer()
{
	return &player;
}
