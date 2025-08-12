#pragma once
#include "Scripts/SceneCore.h"

class Stage1 : public Scene
{
protected:
	void OnEnterImpl() override;
	void OnExitImpl() override;
	void UpdateImpl() override;

private:
	GameObject* PCO;
	GameObject* inputObj;
	GameObject* stageBGI;


	GameObject* escPanel;

	GameObject* SoundStageOne;
};