#pragma once
#include "pch.h"
#include "Platform/D2DRenderManager.h"
#include "BitmapResource.h"
#include <unordered_map>

/// <summary>
/// 리소스 매니저 ( 일단 BitmapResource만 다룸 )
/// </summary>
class ResourceManager
{
public:
	ResourceManager(D2DRenderManager* pManager) : renderManager(pManager) {};

	std::shared_ptr<BitmapResource> CreateBitmapResource(std::wstring filePath);

private:
	D2DRenderManager* renderManager;
	std::unordered_map<std::wstring, std::weak_ptr<BitmapResource>> mapBitmap;
};