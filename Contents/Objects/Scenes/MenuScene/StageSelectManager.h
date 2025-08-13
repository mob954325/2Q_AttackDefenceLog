#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Objects/SliceObject/SliceableObject.h"
#include "Scripts/SceneCore.h"

class StageSelectManager : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;

private:
	void CreateMenuObjects();
	void ChangeImageByClearState(); // 클리어 상태에 따라 이미지를 바꾸는 함수
	std::vector<SliceableObject*> objs;

	bool isSceneChange = false;

	float timer = 0.0f;
	float maxTimer = 1.0f;
};

