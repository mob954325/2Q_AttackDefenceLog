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

};