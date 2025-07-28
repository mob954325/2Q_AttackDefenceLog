#pragma once
#include "../../Engine/Application/Application.h"
class LogicTestApplication : public Application
{
public:
	void Initialize() override;
	void Render() override;
	void Uninitialize() override;
	void Update() override;
};

