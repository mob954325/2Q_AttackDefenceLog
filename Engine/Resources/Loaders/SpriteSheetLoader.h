#pragma once
#include "pch.h"
#include "Datas/SpriteDatas.h"

class SpriteSheetLoader
{
public:
	static void LoadSpriteSheet(const std::wstring& filePath, SpriteSheet& spriteSheet);
};

