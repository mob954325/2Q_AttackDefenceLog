#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Components/Rendering/VignetteEffect.h"
#include "Components/Logic/InputSystem.h"

class TestVignetteObject : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;

private:
	VignetteEffect* vignette{};
	BitmapRenderer* bitmap{};
	InputSystem* input{};

	float value = 0.0f;
};

