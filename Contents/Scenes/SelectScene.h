#pragma once
#include "Scripts/SceneCore.h"

class SelectScene : public Scene
{
protected:
	void OnEnterImpl() override;
	void OnExitImpl() override;
	void UpdateImpl() override;

private:

};