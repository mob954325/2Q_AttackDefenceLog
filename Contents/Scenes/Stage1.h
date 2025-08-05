#pragma once
#include "Scripts/SceneCore.h"
#include "../Objects/Manager/PatternManager.h"

class Stage1 : public Scene
{
protected:
	void OnEnterImpl() override;
	void OnExitImpl() override;
	void UpdateImpl() override;

private:
	GameObject* inputObj;
	GameObject* trail;

	std::array<GameObject*, 9> m_nodes;
	PatternManager PM;
};