#pragma once
#include "Components/Base/Transform.h"
#include "Components/Camera/Camera.h"
#include "Utils/Singleton.h"

struct CameraInfo 
{
	CameraInfo(int& refPriority , Camera* camera) :priority(refPriority), camera(camera) {};

	int& priority;
	Camera* camera{};
};

class CameraManager : public Singleton<CameraManager>
{
public:
	friend class Singleton<CameraManager>;

	void Register(CameraInfo* info);
	void Update();
	void ClearAll();

	Camera* GetActiveCamera() const;
	int GetCameraCount();
private:
	void SortCameras();

	std::vector<CameraInfo*> cameras;
};

