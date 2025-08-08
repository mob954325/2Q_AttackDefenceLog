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

	if (isFlip) mat.m11 = -mat.m11;
	manager->SetRenderTransform(mat);

	// Spirte 정보에 맞게 위치 조정
	destRect = player.GetDestRect();
	srcRect = player.GetSrcRect();

	manager->DrawBitmap(m_bitmapResource.get()->GetBitmap(), destRect, srcRect, capacity);

	player.Update(Singleton<GameTime>::GetInstance().GetDeltaTime());
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
