#include "CameraManager.h"
#include <algorithm>

void CameraManager::Register(CameraInfo* info)
{
	cameras.push_back(info);
	SortCameras();
}

void CameraManager::Update()
{
	if (cameras.empty()) return;

	bool isSort = false;
	for (auto cam : cameras)
	{
		if (cam->camera->IsPriorityChanged())
		{
			SortCameras();
			isSort = true;
			break;
		}
	}

	if (isSort)
	{
		for (auto cam : cameras)
		{
			cam->camera->ResetIsPriorityChanged();
		}
	}
}

void CameraManager::ClearAll()
{
	auto it = cameras.begin();
	for (; it != cameras.end();)
	{
		delete *it;
		it = cameras.erase(it);
	}
}

Camera* CameraManager::GetActiveCamera() const
{
	if (cameras.empty())
	{
		return nullptr;
	}
	else
	{
		return cameras[0]->camera;
	}

}

int CameraManager::GetCameraCount()
{
	return cameras.size();
}

void CameraManager::SortCameras()
{
	sort(cameras.begin(), cameras.end(), [](CameraInfo* info1, CameraInfo* info2)
		{
			return info1->priority < info2->priority;
		});
}
