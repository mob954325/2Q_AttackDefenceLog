#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Objects/SliceObject/SliceableObject.h"
#include "Scripts/SceneCore.h"

class LevelSelectManager : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;

private:
	void CreateMenuObjects();
	std::vector<SliceableObject*> objs;

	bool isSceneChange = false;

	float timer = 0.0f;
	float maxTimer = 1.0f;
};

