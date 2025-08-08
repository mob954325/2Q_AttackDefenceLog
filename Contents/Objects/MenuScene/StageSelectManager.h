#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Objects/SliceObject/SliceableObject.h"

class StageSelectManager : public MonoBehavior
{
public:
	void OnCreate();
	void OnStart();

private:
	void CreateMenuObjects();
	std::vector<SliceableObject*> objs;

	bool isSceneChange = false;
};

