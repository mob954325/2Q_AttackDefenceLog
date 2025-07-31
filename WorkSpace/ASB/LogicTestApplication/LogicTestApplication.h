#pragma once
#include "Application/Application.h"
class GameLogicTestScene;
class LogicTestApplication : public Application
{
public:
	void Initialize() override;
	void Render() override;
	void Uninitialize() override;
	void Update() override;


	GameLogicTestScene* gameLogicTestScene = nullptr;
};

