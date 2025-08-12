#pragma once
#include "Scripts/SceneCore.h"

class MenuScene : public Scene
{
protected:
	void OnEnterImpl() override;
	void OnExitImpl() override;
	void UpdateImpl() override;

private:
	GameObject* testObj;
	GameObject* inputObj;
	GameObject* trail;
	GameObject* backGroundImg;
	GameObject* selectManager;
	GameObject* selectEffectManager;

	GameObject* cloudManager;
};