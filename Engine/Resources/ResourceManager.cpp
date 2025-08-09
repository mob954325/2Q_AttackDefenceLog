#include "ResourceManager.h"

std::shared_ptr<BitmapResource> BitmapResourceManager::CreateBitmapResource(std::wstring filePath)
{
	std::wcout << filePath << std::endl;
	std::shared_ptr<BitmapResource> sharedResource;
	auto it = mapBitmap.find(filePath);

	if (it == mapBitmap.end() || it->second.expired())
	{
		sharedResource = std::make_shared<BitmapResource>();

		ID2D1Bitmap1* outBitmap = nullptr;
		HRESULT hr = renderManager->CreateBitmapFromFile(filePath.c_str(), &outBitmap);

		assert(SUCCEEDED(hr) && "Bitmap load failed !!!!!!!!!!");

		if (FAILED(hr)) {
			char msg[256];
			sprintf_s(msg, "Bitmap load failed! File: %ws, hr=0x%08X", filePath.c_str(), hr);
			OutputDebugStringA(msg);
		}

		sharedResource->SetBitmap(&outBitmap);
		mapBitmap[filePath] = std::weak_ptr<BitmapResource>(sharedResource);
	}
	else
	{
		sharedResource = it->second.lock();
	}

	return sharedResource;
}
