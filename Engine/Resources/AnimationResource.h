#pragma once
#include "pch.h"

struct FrameInfo
{
	std::wstring sprite;	// Sprite 이름
	int spriteSheetIndex;	// Sprite 인덱스
	float duration;			// 프레임 지속시간
};

struct AnimationClip 
{
	std::wstring clipName;			// 애니메이션 클립 이름
	std::wstring texturePath;		// 애니메이션 클립에 사용되는 텍스처 경로
	bool isLoop;					// 애니메이션 루프 여부
	float duration;					// 애니메이션 전체 실행 시간
	std::vector<FrameInfo> frames;	// 프레임 데이터
};