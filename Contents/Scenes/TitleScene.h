#pragma once
#include "Scripts/SceneCore.h"

class TitleScene : public Scene
{
protected:
	void OnEnterImpl() override;
	void OnExitImpl() override;
	void UpdateImpl() override;

private:
	GameObject* nodeManager;
	GameObject* node;
	GameObject* inputObj;
	GameObject* trail;
	GameObject* backGroundImg;



	GameObject* cloudManager;
	GameObject* titleEffectManager;
};