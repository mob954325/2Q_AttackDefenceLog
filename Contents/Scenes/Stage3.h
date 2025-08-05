#pragma once
#include "Scripts/SceneCore.h"

class Stage3 : public Scene
{
protected:
	void OnEnterImpl() override;
	void OnExitImpl() override;
	void UpdateImpl() override;

private:
	GameObject* inputObj;
};