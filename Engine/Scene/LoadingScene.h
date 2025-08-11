#pragma once
#include "Scene/Scene.h"

class LoadingScene : public Scene
{
public:
	void OnEnterImpl() override;
	void OnExitImpl() override;
	void UpdateImpl() override;

	void GetTargetIndexScene(int index);

private:
	int targetSceneIndex = -1; // 전환될 씬 인덱스
};