#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Logic/InputSystem.h"
#include "Components/Camera/Camera.h"
#include "Utils/GameTime.h"

class MainCam : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;

	void CheckInput();
private:
	InputSystem* input{};
	Camera* Came{};

	bool ShakeValue = false;
	float counttime = 0.0f;
	
	float maxtimer = 0.5f;
};

