#pragma once
#include "Datas/SpriteDatas.h"
#include "Datas/AnimationDatas.h"

class AnimationClipLoader
{
public:
	static void LoadAnimationClip(const std::wstring& filePath, AnimationClip& clip, const SpriteSheet& spriteSheet);
};

