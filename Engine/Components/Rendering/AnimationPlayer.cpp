#include "AnimationPlayer.h"
#include "Resources/Loaders/SpriteSheetLoader.h"
#include "Resources/Loaders/AnimationClipLoader.h"

void AnimationPlayer::Update(float delta)
{
	if (isPlay)
	{
		timer += delta;

		if (timer >= clip.duration)
		{
				currentFrameIndex = 0;
				timer = 0.0f;
		}
		else
		{
			if (currentFrameIndex < clip.frames.size() - 1 && timer >= clip.frames[currentFrameIndex].duration)
			{
				currentFrameIndex++;
			}
		}
	}
}

D2D1_RECT_F AnimationPlayer::GetDestRect() const
{
	Sprite currSprite = sheet.sprites[clip.frames[currentFrameIndex].spriteSheetIndex];
	float pivotOffsetX = currSprite.width * currSprite.pivotX;
	float pivotOffsetY = currSprite.height * currSprite.pivotY;

	D2D1_RECT_F destRect =
	{
		0 - pivotOffsetX,
		0 - pivotOffsetY,
		currSprite.width - pivotOffsetX,
		currSprite.height - pivotOffsetY
	};
	return destRect;
}

D2D1_RECT_F AnimationPlayer::GetSrcRect() const
{
	Sprite currSprite = sheet.sprites[clip.frames[currentFrameIndex].spriteSheetIndex];
	float pivotOffsetX = currSprite.width * currSprite.pivotX;
	float pivotOffsetY = currSprite.height * currSprite.pivotY;

	D2D1_RECT_F srcRect =
	{
		currSprite.x,
		currSprite.y,
		currSprite.x + currSprite.width,
		currSprite.y - currSprite.height
	};

	return srcRect;
}

void AnimationPlayer::SetBitmapResource(const BitmapResource& resource)
{
	this->resource = resource;
}

BitmapResource& AnimationPlayer::GetBitmapResource()
{
	return resource;
}

void AnimationPlayer::SetSpriteSheet(std::wstring path)
{
	SpriteSheetLoader::LoadSpriteSheet(path, sheet);
}

SpriteSheet AnimationPlayer::GetSpriteSheet()
{
	return sheet;
}

void AnimationPlayer::SetAnimationClip(std::wstring path)
{
	if (sheet.texture == L"")
	{
		throw std::runtime_error("Fail to open animation clip file, sheet is empty");
	}
	else
	{
		AnimationClipLoader::LoadAnimationClip(path, clip, sheet);
		maxFrameIndex = clip.frames.size();
		currentFrameIndex = 0;
		timer = 0;
	}
}

AnimationClip AnimationPlayer::GetAnimationClip()
{
	return clip;
}

void AnimationPlayer::SetLoop(bool value)
{
	isLoop = value;
}

void AnimationPlayer::SetCurrentFrame(int index)
{
	if (index < 0 || index > maxFrameIndex) return;

	currentFrameIndex = index;
}

int AnimationPlayer::GetCurrentFrame() const
{
	return currentFrameIndex;
}

int AnimationPlayer::GetMaxFrame() const
{
	return maxFrameIndex;
}



void AnimationPlayer::Play()
{
	isPlay = true;
}

void AnimationPlayer::Pause()
{
	isPlay = false;
}

void AnimationPlayer::Reset()
{
	currentFrameIndex = 0;
}
