#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/AnimationRenderer.h"

class DummyEffectAnimation : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;
	void OnUpdate() override;

private:
	AnimationRenderer* anim;

	float timer = 0.0f;
	float maxTimer = 0.8f;
};

