#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/AnimationRenderer.h"

class DummyEffectAnimation : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;

private:
	AnimationRenderer* anim;
};

