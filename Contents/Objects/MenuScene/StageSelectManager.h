#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Objects/SliceObject/SliceableObject.h"

class StageSelectManager : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;

private:
	void CreateMenuObjects();
	std::vector<SliceableObject*> objs;

	bool isSceneChange = false;
};

