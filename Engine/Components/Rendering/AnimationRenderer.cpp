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
	
	// 출력할 최종 위치 설정
	D2D1_MATRIX_3X2_F mat = owner->GetTransform().GetFinalMatrix();

	if (isFlip) mat.m11 = -mat.m11;
	manager->SetRenderTransform(mat);

	// Spirte 정보에 맞게 위치 조정
	Sprite currSprite = sheet.sprites[clip.frames[frameIndex].spriteSheetIndex];
	float pivotOffsetX = currSprite.width * currSprite.pivotX;
	float pivotOffsetY = currSprite.height * currSprite.pivotY;
	destRect =
	{
		0 - pivotOffsetX,
		0 - pivotOffsetY,
		currSprite.width - pivotOffsetX,
		currSprite.height - pivotOffsetY
	};

	srcRect =
	{
		currSprite.x,
		currSprite.y,
		currSprite.x + currSprite.width,
		currSprite.y - currSprite.height
	};

	manager->DrawBitmap(m_bitmapResource.get()->GetBitmap(), destRect, srcRect);

	if (isPlay)
	{
		timer += Singleton<GameTime>::GetInstance().GetDeltaTime();

		if (timer >= clip.duration)
		{
			if (clip.loop)
			{
				frameIndex = 0;
				timer = 0.0f;
			}
		}
		else 
		{
			if (frameIndex < clip.frames.size() - 1 && timer >= clip.frames[frameIndex].duration)
			{
				frameIndex++;
			}
		}
	}
}

void AnimationRenderer::SetSpriteSheet(std::wstring filePath)
{
	SpriteSheetLoader::LoadSpriteSheet(filePath, sheet);
}

void AnimationRenderer::SetAnimationClip(std::wstring filePath)
{
	if (sheet.texture == L"")
	{
		throw std::runtime_error("Fail to open animation clip file, sheet is empty");
	}
	else
	{
		AnimationClipLoader::LoadAnimationClip(filePath, clip, sheet);
		maxFrameIndex = clip.frames.size();
		frameIndex = 0;
		timer = 0;
	}
}