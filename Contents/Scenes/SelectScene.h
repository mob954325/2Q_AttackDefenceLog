#pragma once
#include "Scripts/SceneCore.h"

class SelectScene : public Scene
{
protected:
	void OnEnterImpl() override;
	void OnExitImpl() override;
	void UpdateImpl() override;

private:
	GameObject* inputObj;
	GameObject* testObj;
	GameObject* trail;
	GameObject* selectManager;
	GameObject* SoundSeletObj;
};