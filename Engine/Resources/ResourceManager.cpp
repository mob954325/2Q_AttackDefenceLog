#include "ResourceManager.h"

std::shared_ptr<BitmapResource> BitmapResourceManager::CreateBitmapResource(std::wstring filePath)
{
	std::shared_ptr<BitmapResource> sharedResource;
	auto it = mapBitmap.find(filePath);

	if (it == mapBitmap.end() || it->second.expired())
	{
		sharedResource = std::make_shared<BitmapResource>();

		ID2D1Bitmap1* outBitmap = nullptr;
		renderManager->CreateBitmapFromFile(filePath.c_str(), &outBitmap);
		sharedResource->SetBitmap(&outBitmap);
		mapBitmap[filePath] = std::weak_ptr<BitmapResource>(sharedResource);
	}
	else
	{
		sharedResource = it->second.lock();
	}

	return sharedResource;
}
