#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Components/Rendering/VignetteEffect.h"

class TestVignetteObject : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;

private:
	VignetteEffect* vignette{};
	BitmapRenderer* bitmap{};
};

