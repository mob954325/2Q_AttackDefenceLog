#pragma once
#include "pch.h"
#include "Datas/AnimationControllerDatas.h"

class AnimationControllerLoader
{
public:
	static void LoadAnimatorController(const std::wstring& filePath, AnimatorController& clip);
};