#pragma once
#include "pch.h"

struct FrameInfo
{
	std::wstring sprite;
	int spriteSheetIndex;
	float duration;
};

struct AnimationClip
{
	std::wstring clipName = L"";
	std::wstring texturePath = L"";
	bool loop;
	float duration; // 전체 애니메이션 시간
	std::vector<FrameInfo> frames;
};