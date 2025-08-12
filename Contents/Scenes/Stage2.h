#pragma once
#include "Scripts/SceneCore.h"

class Stage2 : public Scene
{
protected:
	void OnEnterImpl() override;
	void OnExitImpl() override;
	void UpdateImpl() override;

private:
	GameObject* inputObj;
	GameObject* escPanel;
	GameObject* SoundStageTwo;
};